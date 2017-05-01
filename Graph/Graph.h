#pragma once
#include<vector>
#include<unordered_set>
#include <stack>
#include <queue>
#include<string>

#define u32 unsigned int

// the index of the vertices must count from zero
class TGraph
{
public:
	using TAdjs = std::vector<std::unordered_set<u32>>;
	TGraph() = default;
	TGraph(u32 nVertices) { m_adjs_vec.reserve(nVertices); }
	virtual ~TGraph() = default;
	u32 VCount() const { return m_adjs_vec.size(); };
	u32 ECount() const {
		u32 n = 0;
		for (auto &r : m_adjs_vec)
			n += r.size();
		return n / 2;
	}
	TAdjs m_adjs_vec;
	void Add_vertice(u32 vIdx)
	{
		if (m_adjs_vec.size() <= vIdx)
			m_adjs_vec.resize(vIdx + 1);
	}
	void Add_edge(u32 v, u32 w)
	{
		Add_vertice(v); Add_vertice(w);
		m_adjs_vec[v].emplace(w);
		m_adjs_vec[w].emplace(v);
	}

	template<typename ...T>
	void Add_edge(u32 v, u32 w, T&&... rest)
	{
		Add_edge(v, w);
		Add_edge(std::forward<T>(rest)...);
	}
};

//depth first search gives you probably not the shortest path, this is the nature of this algorithm
// in contrast, the breath first search will give the shortest path.

// you could use BFS()->Getpath
//or DFS()->Getpath or 
// DFS_recursive_and_mark_if_acylic()->Getpath/IsAsylic
class TGraph_search
{
public:
	TGraph_search(const TGraph* pGraph, u32 source) : m_pGraph(pGraph), m_src(source)
	{
		m_infos.resize(pGraph->VCount(), { false, 0 }); // adapt the size of the marked
	};

	// this method will call BFS, which will give you the shortest path
	void BFS()
	{
		std::queue<u32> q;
		q.push(m_src);
		m_infos[m_src].marked = true;
		while (!q.empty())
		{
			u32 current = q.front();
			q.pop();
			auto& adjs = m_pGraph->m_adjs_vec[current];
			for (auto &iAdj : adjs)
			{
				TVInfo& info = m_infos[iAdj]; //info related to the reached node
				if (!info.marked)
				{
					info.parent = current;
					info.marked = true;
					q.push(iAdj);
				}
			}
		}
	}

	// this one will call dfs and will not calculate whether it is asylic
	void DFS()
	{
		std::stack<u32> v;
		v.push(m_src);
		m_infos[m_src].marked = true;
		while (!v.empty())
		{
			u32 current = v.top();
			auto& adjs = m_pGraph->m_adjs_vec[current];
			for (auto &iAdj : adjs)
			{
				TVInfo& info = m_infos[iAdj]; //info related to the reached node
				if (!info.marked)
				{
					info.parent = current;
					m_infos[iAdj].marked = true;
					v.push(iAdj);
					break;
				}
				v.pop(); //only when we have finished all its neighbors, could we pop it
			}
		}
	}
	// this function will do a DFS and get whether the graph is asyclic
	void DFS_recursive()
	{
		m_infos[m_src].marked = true;
		DFS_recursive(m_src);
	}

	void DFS_recursive(u32 father)
	{
		// the adjacents to father
		auto& adjs = m_pGraph->m_adjs_vec[father];
		//loop all the adjacents, mark it if not marked, and do deep on that
		for (auto &iAdj : adjs)
		{
			TVInfo& info = m_infos[iAdj]; //info related to the reached node
			if (!info.marked)
			{
				info.marked = true;
				info.parent = father;
				DFS_recursive(iAdj); //go deep!emplace
			}	// this function will do a DFS and get whether the graph is asyclic
		}
	}
	void DFS_recursive_and_mark_if_acylic()
	{
		m_infos[m_src].marked = true;
		DFS_recursive_and_mark_if_acylic(m_src, m_src);
	}

	void DFS_recursive_and_mark_if_acylic(u32 father, u32 grandfather)
	{
		// the adjacents to father
		auto& adjs = m_pGraph->m_adjs_vec[father];
		//loop all the adjacents, mark it if not marked, and do deep on that
		for (auto &iAdj : adjs) 
		{
			TVInfo& info = m_infos[iAdj]; //info related to the reached node
			if (!info.marked)
			{
				info.marked = true;
				info.parent = father;
				DFS_recursive_and_mark_if_acylic(iAdj, father); //go deep!emplace
			}
			else
			{
				//It is marked, it is somebody else's son.
				//It is an adj of father and it is not the grandfather, then it must be the father's son
				// if it has two fathers, this is no longer a tree
				if (iAdj != grandfather)
					m_isAsylic = false;
			}
		}
	}



	// this function will do a DFS and get whether the graph is asyclic
	void DFS_recursive_and_mark_if_two_colorable()
	{
		m_colors.resize(m_pGraph->VCount(), true);
		m_isTwoColorable = true;

		m_infos[m_src].marked = true;
		DFS_recursive_and_mark_if_two_colorable(m_src);
	}

	void DFS_recursive_and_mark_if_two_colorable(u32 root)
	{
		// the adjacents to father
		auto& adjs = m_pGraph->m_adjs_vec[root];
		//loop all the adjacents, mark it if not marked, and do deep on that
		for (auto &iAdj : adjs)
		{
			TVInfo& info = m_infos[iAdj]; //info related to the reached node
			if (!info.marked)
			{
				info.marked = true;
				info.parent = root;
				DFS_recursive_and_mark_if_two_colorable(iAdj); //go deep!emplace
				m_colors[iAdj] = !m_colors[root];
			}
			else
			{
				if (m_colors[iAdj] == m_colors[root])
					m_isTwoColorable = false;
			}
		}
	}

	bool IsAsylic()
	{
		return m_isAsylic;
	}
	std::vector<u32> get_path(u32 dst)
	{
		if (!m_infos[dst].marked)
			return {};
		std::vector<u32> path;
		u32 currentNode = dst;
		while (currentNode != m_src)
		{
			path.emplace_back(currentNode);
			currentNode = m_infos[currentNode].parent;
		}
		path.emplace_back(m_src);
		return path;
	}


private:
	bool m_isAsylic{ false };
	bool m_isTwoColorable{ true };
	const TGraph* m_pGraph;
	u32 m_src;
	struct TVInfo
	{
		bool marked;
		u32 parent;
	};
	std::vector<TVInfo> m_infos;
	std::vector<bool> m_colors;

};

class TGraph_Connectivity
{
public:
	TGraph_Connectivity(const TGraph* pGraph) : m_pGraph(pGraph)
	{
		m_infos.resize(pGraph->VCount(), { false, 0 }); // adapt the size of the marked
	};

	void DFS()
	{
		for (u32 iV = 0; iV < m_pGraph->VCount(); iV++)
		{
			if(!m_infos[iV].marked)
			{
				DFS(iV);
				m_nComponents++;
			}
		}
	}

	u32 GetComponentsCount()
	{
		return m_nComponents;
	}

	bool Connected(u32 m, u32 n)
	{
		return m_infos[m].id == m_infos[n].id;
	}

	u32 GetId(u32 m)
	{
		return m_infos[m].id;
	}

private:
	void DFS(u32 src)
	{
		m_infos[src].marked = true;
		m_infos[src].id = m_nComponents;
		auto &adjs = m_pGraph->m_adjs_vec[src];
		for (auto &iAdj : adjs)
		{
			auto& info = m_infos[iAdj];
			if (!info.marked)
				DFS(iAdj);
		}
	}
	const TGraph* m_pGraph;
	struct TVInfo
	{
		bool marked;
		u32 id;
	};
	std::vector<TVInfo> m_infos;
	u32 m_nComponents{ 0 };
};
#pragma once
// the index of the vertices must count from zero
#include<vector>
#include<unordered_set>
#include <stack>
#include <queue>
#include<string>

#define u32 unsigned int

class TDigraph
{
public:
	using TAdjs = std::vector<std::unordered_set<u32>>;
	TDigraph() = default;
	TDigraph(u32 nVertices) { m_adjs_vec.reserve(nVertices); }
	virtual ~TDigraph() = default;
	u32 VCount() { return m_adjs_vec.size(); };
	u32 ECount() {
		u32 n = 0;
		for (auto &r : m_adjs_vec)
			n += r.size();
	}
	TAdjs m_adjs_vec;
	void Add_vertice(u32 vIdx)
	{
		if (m_adjs_vec.size() <= vIdx)
			m_adjs_vec.resize(vIdx + 1);
	}
	// add an edge directed from v to w
	void Add_edge(u32 v, u32 w)
	{
		Add_vertice(v); Add_vertice(w);
		m_adjs_vec[v].emplace(w); 
	}
};

//depth first search gives you probably not the shortest path, this is the nature of this algorithm
// in contrast, the breath first search will give the shortest path.
class TDigraph_multi_src_connectivity
{
public:
	TDigraph_multi_src_connectivity(TDigraph* pGraph) : m_pGraph(pGraph)
	{
		m_infos.resize(pGraph->VCount(), { false, 0 }); // adapt the size of the marked
	};
	TDigraph* m_pGraph;
	u32 m_src{ 0 };
	struct TVInfo
	{
		bool marked;
		u32 parent;
	};
	std::vector<TVInfo> m_infos;
	void DFS_recursive(std::vector<u32> sources)
	{
		for (auto &src : sources)
			if (!m_infos[src].marked)
			{
				m_infos[src].parent = src; // these sources should point to themselves
				DFS_recursive(src);
			}
	}

	void DFS_recursive(u32 root)
	{
		m_infos[root].marked = true;
		// the adjacents to current root
		auto& adjs = m_pGraph->m_adjs_vec[root];
		//loop all the adjacents, mark it if not marked, and do deep on that
		for (auto &iAdj : adjs)
		{
			TVInfo& info = m_infos[iAdj]; //info related to the reached node
			if (!info.marked)
			{
				info.marked = true;
				info.parent = root;
				DFS_recursive(iAdj); //go deep!
			}
		}
	}
	std::vector<u32> get_path(u32 dst)
	{
		if (!m_infos[dst].marked)
			return {};
		std::vector<u32> path;
		u32 currentNode = dst;
		while (m_infos[currentNode].parent != currentNode)
		{
			path.emplace_back(currentNode);
			currentNode = m_infos[currentNode].parent;
		}
		path.emplace_back(m_src);
		return path;
	}

	bool IsVerticeConnected(u32 v)
	{
		return m_infos[v].marked;
	}
};


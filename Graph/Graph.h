#pragma once
#include<vector>
#include<string>
#include<Search/inc/seq_search_unordered_map.h>

using u32 = unsigned int;

// the index of the vertices must count from zero
class TGraph
{

public:
	friend void SearchGraph(TGraph, u32);

	using TAdjs = std::vector<TBag<u32>>;
	TGraph() = default;
	TGraph(u32 nVertices) { m_vertices.resize(nVertices); }
	virtual ~TGraph() = default;
	u32 VCount() { return m_vertices.size(); };
	u32 ECount() {
		u32 n = 0;
		for (auto &r : m_vertices)
			n += r.size();
		return n / 2;
	}
	TAdjs m_vertices;
	void Add_vertice(u32 vIdx)
	{
		if (m_vertices.size() <= vIdx)
			m_vertices.resize(vIdx + 1);
	}
	void Add_edge(u32 v, u32 w)
	{
		Add_vertice(v); Add_vertice(w);
		m_vertices[v].put(w);
		m_vertices[w].put(v);
	}
};

void SearchGraph(TGraph graph, u32 source)
{

}
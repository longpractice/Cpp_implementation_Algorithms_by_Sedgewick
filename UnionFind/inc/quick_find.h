/*
 * quick_find.h
 *
 *  Created on: Nov 11, 2016
 *      Author: Yang
 */

#ifndef QUICK_FIND_H_
#define QUICK_FIND_H_


#include <memory>
#include "types.h"
class TQuickFindUF
{
public:
	TQuickFindUF(){};
	virtual ~TQuickFindUF(){};
	void Init(u32 _nSites)
	{
		m_n_sites = _nSites;
		std::unique_ptr<TSiteInfo[]> tmp_ptr(new TSiteInfo[m_n_sites]);
		m_sites = std::move(tmp_ptr);

		for (u32 iSite = 0; iSite < m_n_sites; iSite++)
			m_sites[iSite].parent_id = iSite; // At the beginning, each site form a union. So it is its own root.

		m_n_unions = _nSites; // there are as many unions as sites
	}

	u32 Unions_count()
	{
		return m_n_unions;
	}

	bool Connected(u32 _site_p, u32 _site_q)
	{
		return Find(_site_p) == Find(_site_q);
	}

	// return whether they are connected already
	bool Union(u32 _site_p, u32 _site_q)
	{
		auto root_p_id = Find(_site_p);
		auto root_q_id = Find(_site_q);
		if (root_p_id == root_q_id)
			return true;
		else
		{
			for(u32 iSite = 0; iSite < m_n_sites; iSite++)
			{
				if (m_sites[iSite].parent_id == root_p_id)
					m_sites[iSite].parent_id = root_q_id;
			}
			m_n_unions--;
			return false;
		}
	}

private:
	struct TSiteInfo
	{
		u32 parent_id;
	};

	u32 Find(u32 _site_idx)
	{
		return (m_sites[_site_idx].parent_id);
	}
	std::unique_ptr<TSiteInfo[]> m_sites; // in order to facilitate garbage collection
	u32 m_n_unions{ 0 }; // total number of unions
	u32 m_n_sites{ 0 };
};


#endif /* QUICK_FIND_H_ */

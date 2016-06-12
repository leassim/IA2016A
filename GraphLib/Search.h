#pragma once
#include "GraphManager.h"
#include <queue>
class CSearch
{
public:
	CSearch();
	virtual ~CSearch();
	bool DFS(CGraph *pG, long source, long dest);
	bool BFS(CGraph *pG, long source, long dest);
	void ClearSearch(CGraph*pG);
	bool HC(CGraph *pG, long source, long dest);
	float hipt(CGraph *pG, long source, long dest);
	bool BF(CGraph *pG, long source, long dest);
};



#include "stdafx.h"
#include "Search.h"
#include "Arrow.h"
#include "Graph.h"
#include "GraphManager.h"
#include "Vertex.h"
#include "Edge.h"
#include <list>
#include <math.h>
#include <fstream>
#include <iostream>
using namespace std;


CSearch::CSearch()

{
}


CSearch::~CSearch()
{
}

bool CSearch::DFS(CGraph *pG, long source, long dest) 
{
	set<long long>  expansion;
	pG->AdjOutput(source, expansion);
	union { struct { long first, second; }; long long llID; };
	for (auto v : expansion) 
	{
		llID = v;
		CVertex *pV = pG->GetGraphManager().CreateVertex(second);
		if (!pV->GetVisit()) 
		{
			pV->SetVisit(true);
			pV->SetParent(first);
			if (pV->Key() == dest) 
			{
				return true;
			}
			if (DFS(pG, pV->Key(), dest)) 
			{
				return true;
			}
		}
	}
	return false;
}

bool CSearch::BFS(CGraph *pG, long source, long dest)
{
	queue <long> Q;
	Q.push(source);
	CVertex *pV = pG->GetGraphManager().CreateVertex(source);
	pV->SetVisit(true);
	while (!Q.empty()) 
	{
		auto v = Q.front();
		Q.pop();
		set<long long>  expansion;
		pG->AdjOutput(v, expansion);
		for (auto index : expansion) 
		{
			union { struct { long first, second; }; long long llID; };
			llID = index;
			auto w = second;
			pV = pG->GetGraphManager().CreateVertex(w);
			if (!pV->GetVisit()) 
			{
				pV->SetVisit(true);
				pV->SetParent(v);
				Q.push(w);
				if (w == dest) 
				{
					return true;
				}
			}
		}
	}
	return false;
}
void CSearch::ClearSearch(CGraph *pG)
{
	set<long> m_setvetex = pG->m_V;
	for (auto v : m_setvetex) 
	{
		CVertex *pV = pG->GetGraphManager().CreateVertex(v);
		pV->SetParent(-1);
		pV->SetVisit(false);
		pV->foam = 0;
		pV->cost = 0;
	}
}

bool CSearch::HC(CGraph *pG, long source, long dest) // Acenso a la colina
{
	//Sea G(V, E) un grafo, OL la lista de abiertos y CL la lista de cerrados.Ademas sea 'o'el nodo origen y 'm' el nodo meta :
	//
	list<pair<float, long>> OL = {};
	list<pair<float, long>> Ex = {};
	list<long> CL = {};
	float foam;
	long key;
	bool bandera = false;
	CVertex *Pv = pG->GetGraphManager().CreateVertex(source);
	CVertex *Pd = pG->GetGraphManager().CreateVertex(dest);
	CVertex *Pa;
	foam = Pv->foam;
	key = Pv->Key();
	OL.push_front(make_pair(Pv->foam, Pv->Key())); 
	CL.push_front(key);
	while (!OL.empty())
	{
		auto v = OL.front();
		Pv = pG->GetGraphManager().CreateVertex(v.second);
	 	OL.pop_front();
		CL.push_front(Pv->Key());
		if (v.second == dest)
		{
			return true;
		}
		set<long long>  expansion;
		pG->AdjOutput(v.second, expansion);
		for (auto index : expansion)
		{
			union { struct { long first, second; }; long long llID; };
			llID = index;
			auto w = second;
			Pa = pG->GetGraphManager().CreateVertex(w);
			for (auto it = CL.begin(); it != CL.end(); it++)
			{
				if (Pa->Key() == *it)
				{
					bandera = true;
				}
			}
			if (bandera == false)
			{
				Pa->SetParent(v.second);
				Pa->cost = Pv->cost + hipt(pG, Pv->Key(), Pa->Key());
				Pa->foam = Pa->cost + hipt(pG, Pa->Key(), Pd->Key());
				Ex.push_front(make_pair(Pa->foam, Pa->Key()));

			}
			if (bandera == true)
				bandera = false;
				
		}
		Ex.sort();
		while (!Ex.empty())
		{
			auto it = Ex.back();
			Ex.pop_back();
			OL.push_front(make_pair(it.first, it.second));
		}
	}
   return false;

	

}

float CSearch::hipt(CGraph *pG,long source,long dest) //heuristica
{
	
		CVertex *pV1 = pG->GetGraphManager().CreateVertex(source);
		CVertex *pV2 = pG->GetGraphManager().CreateVertex(dest);
		float x1, x2, y1, y2,x,y,hipotenusa;
		x1 = pV1->x;
		y1 = pV1->y;
		x2 = pV2->x;
		y2 = pV2->y;
		x=abs(x2 - x1);
		y=abs(y2 - y1);
		sqrt(x*x + y*y);
		hipotenusa= sqrt(x*x + y*y);
		return hipotenusa;
		
}
bool CSearch::BF(CGraph *pG, long source, long dest)// primero el mejor
 {
	//Sea G(V, E) un grafo, OL la lista de abiertos y CL la lista de cerrados.Ademas sea 'o'el nodo origen y 'm' el nodo meta :
	//
	list<pair<float, long>> OL = {};
	float foam;
	long key;
	CVertex *Pv = pG->GetGraphManager().CreateVertex(source);
	CVertex *Pd = pG->GetGraphManager().CreateVertex(dest);
	CVertex *Pa;
	foam = Pv->foam;
	key = Pv->Key();
	OL.push_back(make_pair(foam, key));
	Pv->SetVisit(true);
	while (!OL.empty())
	{
		auto v = OL.front();
		OL.pop_front();
		Pv = pG->GetGraphManager().CreateVertex(v.second);
		
		if (v.second == dest)
		{

			return true;
		}
		set<long long>  expansion;
		pG->AdjOutput(v.second, expansion);
		for (auto index : expansion)
		{
			union { struct { long first, second; }; long long llID; };
			llID = index;
			auto w = second;
			Pa = pG->GetGraphManager().CreateVertex(w);
			if (!Pa->GetVisit())
			{
				Pa->SetVisit(true);
				Pa->SetParent(v.second);
				Pa->cost = Pv->cost + hipt(pG, Pv->Key(), Pa->Key());
				Pa->foam = Pa->cost + hipt(pG, Pa->Key(), Pd->Key());
				OL.push_back(make_pair(Pa->foam, Pa->Key()));
			}
		}
		OL.sort();


	}


	return false;
}
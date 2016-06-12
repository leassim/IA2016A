#include "stdafx.h"
#include "GraphManager.h"
#include "Vertex.h"
#include "Edge.h"
#include "Graph.h"
#include <stack>
#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <vector>
using namespace std;

CGraphManager::CGraphManager()
{
}


CGraphManager::~CGraphManager()
{
	Clean();
}

// Crea un vértice con el identificador especificado, si el vértice ya existe con ese ID, entonces se retorna la instancia previa.
CVertex* CGraphManager::
CreateVertex(long lID)
{
	auto it = m_mapVertex.find(lID);
	if (it == m_mapVertex.end())
	{
		auto *v = new CVertex();
		v->m_lID = lID;
		m_mapVertex.insert(make_pair(lID, v));
		return v;
	}
	return it->second;
}


// Crea una arista con las claves de los vértices asociados.Si la aristaya existe, retorna la arista previa.
CEdge* CGraphManager::CreateEdge(long lIDFirst, long lIDSecond)
{
	auto a = CreateVertex(lIDFirst);
	auto b = CreateVertex(lIDSecond);
	union
	{
		struct { long first; long second; };
		long long llID;
	};
	first = lIDFirst;
	second = lIDSecond;
	auto itE = m_mapEdge.find(llID);
	if (itE == m_mapEdge.end())
	{
		auto e = new CEdge();
		e->m_lFirst = lIDFirst;
		e->m_lSecond = lIDSecond;
		m_mapEdge.insert(make_pair(llID, e));
		return e;
	}
	return itE->second;
}

// Crea un grafo, si existe, retorna el existente
CGraph* CGraphManager::CreateGraph(long lIDGraph)
{
	map<long, CGraph*>::iterator it;
	it = m_mapGraph.find(lIDGraph);
	if (it == m_mapGraph.end())//El grafo no existe, se debe crear uno nuevo
	{
		CGraph* pNewGraph = new CGraph(lIDGraph, this);
		return (m_mapGraph.insert(make_pair(lIDGraph, pNewGraph)).first->second);
	}
	return (it->second);
}


//Destriur un grafo
void CGraphManager::DestroyGraph(long lIDGraph)
{
	/*auto it = m_mapGraph.find(lIDGraph);
	if (it != m_mapGraph.end())
	{
		CGraph* pG = new CGraph;
		pG->m_lIDGraph= lIDGraph;
		m_mapGraph.insert(make_pair(lIDGraph));
	}*/
	map<long, CGraph*>::iterator it;
	it = m_mapGraph.find(lIDGraph);
	if (it != m_mapGraph.end()) //El grafo existe, eliminarlo
	{
		delete it->second;
		m_mapGraph.erase(it);
	}
}


void CGraphManager::Clean()
{
	for (map<long, CGraph*>::iterator it = m_mapGraph.begin();it != m_mapGraph.end();it++)
	{
		delete it->second;
	}
	m_mapGraph.clear();
	for (map<long long, CEdge*>::iterator it = m_mapEdge.begin();it != m_mapEdge.end();it++)
	{
		delete it->second;
	}
	m_mapEdge.clear();
	for (map<long, CVertex*>::iterator it = m_mapVertex.begin();it != m_mapVertex.end();it++)
	{
		delete it->second;
	}
	m_mapVertex.clear();
	return void();
}
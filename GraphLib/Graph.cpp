#include "stdafx.h"
#include "Graph.h"
#include "GraphManager.h"
#include "Vertex.h"
#include "Arrow.h"
#include "Search.h"

CGraph::CGraph(int nIDGrapg, CGraphManager* pGraphManager)
{
	m_lIDGraph = nIDGrapg;
	m_pGraphManager = pGraphManager;
}


CGraph::~CGraph()
{
}

int CGraph::Key()
{
	return	m_lIDGraph;
}

CGraphManager& CGraph::GetGraphManager()
{
	return *m_pGraphManager;
}

void CGraph::Connect(long lFirst, long lSecond)
{
	m_V.insert(lFirst);
	m_V.insert(lSecond);

	GetGraphManager().CreateVertex(lFirst);
	GetGraphManager().CreateVertex(lSecond);
	m_E.insert(GetGraphManager().CreateEdge(lFirst, lSecond)->Key());
}

bool CGraph::ConnectWindow(long lIDFirst, long lIDSecond)
{
	union { struct { long first, second; }; long long llID; };
	first = lIDFirst;
	second = lIDSecond;
	m_E.insert(llID);
	m_V.insert(first);
	m_V.insert(second);
	//formas de entrada y salida mas eficientes en un arbol binario.
	m_mapAdjOutput.insert(make_pair(first, llID));
	m_mapAdjInput.insert(make_pair(second, llID));
	return true;
}
void CGraph::AdjOutput(long lID, set<long long>& Outputs)
{
	auto r= m_mapAdjOutput.equal_range(lID);
	for (auto it = r.first; it != r.second; it++)
	{
		Outputs.insert(it->second);
	}
}
void CGraph::AdjInput(long lID, set<long long>& Inputs)
{
	auto r = m_mapAdjInput.equal_range(lID);
	for (auto it = r.first; it != r.second; it++)
	{
		Inputs.insert(it->second);
	}
}
long CGraph::HitTest(int x, int y, CGraphManager* pU)
{
	for (auto v : m_V)
	{
		CVertex* pV=pU->CreateVertex(v);
		float i, j;
		i = x - pV->x;
		j = y - pV->y;
		// x^2+y^2<=r^2 indica si(x,y) está dentro del circulo
		i *= i;
		j *= j;
		if (i + j <= 100)
			return v;
		
	}
	return -1;
}
void CGraph::Draw(HDC hdc, CGraphManager* pU)
{
	union 
	{ 
		struct 
		{ 
			long first, second; 
		}; 
		long long llID;
	};
	for (auto e : m_E)
	{
		llID = e;
		CVertex *pV0, *pV1;
		pV0 = pU->CreateVertex(first);
		pV1 = pU->CreateVertex(second);
		MoveToEx(hdc, (int)pV0->x, (int)pV0->y, NULL);
		//insertar hasta 15 lineas de codigo aqui para las flechitas
		float pi = 3.14159265359;
		ARROWSTRUCT a = { 20,pi / 18,true };
		ArrowTo(hdc, (int)pV1->x, (int)pV1->y,&a);
	}
	for (auto v : m_V)
	{
		CVertex *pV = pU->CreateVertex(v);
		Ellipse(hdc, pV->x - 10, pV->y - 10, pV->x + 10, pV->y + 10);
		TextOutA(hdc, pV->x, pV->y, pV->m_strName.c_str(), pV->m_strName.length());
	}
}
/*void CGraph::Draw2(HDC hdc, CGraphManager* pU)
{
	union
	{
		struct
		{
			long first, second;
		};
		long long llID;
	};
	for (auto e : m_E)
	{
		llID = e;
		CVertex *pV0, *pV1;
		pV0 = pU->CreateVertex(first);
		pV1 = pU->CreateVertex(second);
		MoveToEx(hdc, (int)pV0->x, (int)pV0->y, NULL);
		//insertar hasta 15 lineas de codigo aqui para las flechitas
		float pi = 3.14159265359;
		ARROWSTRUCT a = { 10,pi / 18,false };
		if (pV1->GetParent==pV0->m_lID)
		ArrowTo(hdc, (int)pV1->x, (int)pV1->y, &a);
	}
}*/
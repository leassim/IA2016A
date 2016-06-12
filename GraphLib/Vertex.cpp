#include "stdafx.h"
#include "Vertex.h"
#include <string>


CVertex::CVertex()
{
}


CVertex::~CVertex()
{
}

long CVertex::Key()
{
	return m_lID;
}

void CVertex::SetVisit(bool a)
{
	Visited = a;
}

bool CVertex::GetVisit()
{
	return Visited;
}

void CVertex::SetParent(int v)
{
	Parent = v;
}
int CVertex::GetParent()
{
	return Parent;
}
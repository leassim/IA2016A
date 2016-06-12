#include "stdafx.h"
#include "Edge.h"


CEdge::CEdge()
{
}


CEdge::~CEdge()
{
}

long CEdge::lFirst()
{
	return m_lFirst;
}

long CEdge::lSecond()
{
	return m_lSecond;
}

long long CEdge::Key()
{
	return m_llID;
}

#pragma once
#include <string>
using namespace std;
class CVertex
{
	friend class CGraphManager;
	friend class CGraph;
private:
	int Parent=-1;
	bool Visited=false;
//private:
	//long m_lID;
protected:
	long m_lID;
	long lParent;
	CVertex();
	virtual ~CVertex();
public:
	string 
		m_strName;
	long Key();
	float x, y;
	void SetVisit(bool a);
	bool GetVisit();
	void SetParent(int v);
	int GetParent();
	float foam=0;
	float cost=0;

};


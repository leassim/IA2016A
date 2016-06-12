#pragma once
#include <string>
#include <set>
#include <map>
#include <Windows.h>
using namespace std;

class CGraph
{
	friend class CGraphManager;
private:
	long m_lIDGraph;
	CGraphManager* m_pGraphManager;
protected:
	CGraph(int nIDGrapg, CGraphManager* pGraphManager);
	virtual ~CGraph();
	multimap<long, long long> m_mapAdjInput;
	multimap<long, long long> m_mapAdjOutput;
public:
	set<long> m_V;
	set<long long> m_E;
	int Key();
	CGraphManager &GetGraphManager();
	void Connect(long lFirst, long lSecond);
	bool ConnectWindow(long lIDFirst, long lIDSecond);
	//void Draw2(HDC hdc, CGraphManager* pU);
	void Draw(HDC hdc, CGraphManager* pU);
	void AdjOutput(long lID,set<long long>& Outputs);
	void AdjInput(long lID, set<long long>& Inputs);
	long HitTest(int x, int y, CGraphManager* pU);
};

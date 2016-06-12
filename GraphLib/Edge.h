#pragma once
#include <string>
using namespace std;

class CEdge
{
	friend class CGraphManager;
private:
	union
	{
		struct 
		{ 
			long m_lFirst;
			long m_lSecond;
		};
		long long m_llID;
	};
protected:
	CEdge();
	virtual ~CEdge();
public:
	long lFirst();
	long lSecond();
	long long Key();

};


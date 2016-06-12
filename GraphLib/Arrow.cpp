#include "stdafx.h"
#include "Arrow.h"
#include <math.h> 

//----------------------------------------------------------------------- 

void ArrowTo(HDC hDC, int x, int y, ARROWSTRUCT *pA)
{
	//POINT pCenter = { 300,300 };
	//MoveToEx(hDC, 0, 0, &pCenter);

	//POINT ptTo = {100+ x/sqrt((x*x)+(y*y)), 100+y / sqrt((x*x) + (y*y)) };

	POINT ptTo = { x,y };
	ArrowTo(hDC, &ptTo, pA);
}
//----------------------------------------------------------------------- 

void ArrowTo(HDC hDC, const POINT *lpTo, ARROWSTRUCT *pA)
{
	//auto X = lpTo->x, Y = lpTo->y;
	//int Mag=100;
	POINT pFrom, pBase, aptPoly[3];
	float vecLine[2], vecLeft[2], fLength, th, ta;

	MoveToEx(hDC, 0, 0, &pFrom);

	//pUnitary.x = (X / (sqrt(X*X + Y*Y)));
	//pUnitary.y = (Y / (sqrt(X*X + Y*Y)));
	//pUnitary.x = (lpTo->x / (sqrt(lpTo->x*lpTo->x + lpTo->y*lpTo->y)));//
	//pUnitary.y = (lpTo->y / (sqrt(lpTo->x*lpTo->x + lpTo->y*lpTo->y)));//

	//aptPoly[0].x = lpTo->x;
	//aptPoly[0].y = lpTo->y;

	aptPoly[0].x = lpTo->x;
	aptPoly[0].y = lpTo->y;

	//aptPoly[0].x = pUnitary.x*200;
	//aptPoly[0].y = pUnitary.y*200;

	vecLine[0] = (float)aptPoly[0].x - pFrom.x;
	vecLine[1] = (float)aptPoly[0].y - pFrom.y;

	vecLeft[0] = -vecLine[1];
	vecLeft[1] = vecLine[0];

	fLength = (float)sqrt(vecLine[0] * vecLine[0] + vecLine[1] * vecLine[1]);
	/*float a, b;//
	a = Mag * vecLine[0] / sqrt(vecLine[0] * vecLine[0] + vecLine[1] * vecLine[1]);//
	b = Mag * vecLine[1] / sqrt(vecLine[0] * vecLine[0] + vecLine[1] * vecLine[1]);//
	fLength = (float)sqrt(a*a+b*b);//*/

	th = pA->nWidth / (3.0f * fLength);
	ta = pA->nWidth / (3.0f * (tanl(pA->fTheta*57.29578) / 2.0f) * fLength);

	pBase.x = (int)(aptPoly[0].x + -ta * vecLine[0]);
	pBase.y = (int)(aptPoly[0].y + -ta * vecLine[1]);

	aptPoly[1].x = (int)(pBase.x + th * vecLeft[0]);
	aptPoly[1].y = (int)(pBase.y + th * vecLeft[1]);
	aptPoly[2].x = (int)(pBase.x + -th * vecLeft[0]);
	aptPoly[2].y = (int)(pBase.y + -th * vecLeft[1]);

	MoveToEx(hDC, pFrom.x, pFrom.y, NULL);

	if (pA->bFill) {
		LineTo(hDC, aptPoly[0].x, aptPoly[0].y);
		Polygon(hDC, aptPoly, 3);
	}
	else {
		/*LineTo(hDC, pBase.x, pBase.y);
		LineTo(hDC, aptPoly[1].x, aptPoly[1].y);
		LineTo(hDC, aptPoly[0].x, aptPoly[0].y);
		LineTo(hDC, aptPoly[2].x, aptPoly[2].y);
		LineTo(hDC, pBase.x, pBase.y);*/
		LineTo(hDC, aptPoly[0].x, aptPoly[0].y);
		LineTo(hDC, aptPoly[1].x, aptPoly[1].y);
		LineTo(hDC, aptPoly[0].x, aptPoly[0].y);
		LineTo(hDC, aptPoly[2].x, aptPoly[2].y);
		MoveToEx(hDC, aptPoly[0].x, aptPoly[0].y, NULL);
	}
}
//--------------------------------------------------------------------------------------------------- 

CArrow::CArrow()
{
}


CArrow::~CArrow()
{
}

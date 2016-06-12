// GraphLab.cpp: define el punto de entrada de la aplicación.
//

#include "stdafx.h"
#include "GraphLab.h"
#include <math.h>
#include <complex.h>
#include <fstream>
#include <list>
#include "..\GraphLib\GraphManager.h"
#include "..\GraphLib\Graph.h"
#include "..\GraphLib\Edge.h"
#include "..\GraphLib\Vertex.h"
#include "..\GraphLib\Arrow.h"
#include "..\GraphLib\Search.h"
#include <iostream>
#include <string>
using namespace std;

//#define fuente 1
//#define destino 4
#define MAX_LOADSTRING 100

using namespace std;

// Variables globales:
HINSTANCE hInst;                                // Instancia actual
WCHAR szTitle[MAX_LOADSTRING];                  // Texto de la barra de título
WCHAR szWindowClass[MAX_LOADSTRING];            // nombre de clase de la ventana principal

// Declaraciones de funciones adelantadas incluidas en este módulo de código:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: colocar código aquí.

    // Inicializar cadenas globales
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_GRAPHLAB, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Realizar la inicialización de la aplicación:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_GRAPHLAB));

    MSG msg;

    // Bucle principal de mensajes:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCIÓN: MyRegisterClass()
//
//  PROPÓSITO: registrar la clase de ventana.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

	//fstream pic;
		//		pic.open("..\\Descargas\\mapaCeti.png");


    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_GRAPHLAB));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
//	wcex.hbrBackground = HBRUSH(pic);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_GRAPHLAB);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCIÓN: InitInstance(HINSTANCE, int)
//
//   PROPÓSITO: guardar el identificador de instancia y crear la ventana principal
//
//   COMENTARIOS:
//
//        En esta función, se guarda el identificador de instancia en una variable común y
//        se crea y muestra la ventana principal del programa.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Almacenar identificador de instancia en una variable global

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCIÓN: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PROPÓSITO:  procesar mensajes de la ventana principal.
//
//  WM_COMMAND  - procesar el menú de aplicaciones
//  WM_PAINT    - Pintar la ventana principal
//  WM_DESTROY  - publicar un mensaje de salida y volver
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static float fTime;
	static float mx=300,mx1;
	static float my=300,my1;
	static bool bDragging;
	static CGraphManager U;
	static CGraph* pG;
	static CSearch* pS;
	static int bandera=0;
	static long fuente=-1, destino=-1;
	static set<long long> Edges;
	static long SelectedVertex=-1;
	static CVertex *vLog;
    switch (message)
    {
	case WM_LBUTTONDOWN:
		mx = LOWORD(lParam); // lParam&0x0000ffff;
		my = HIWORD(lParam); // lParam&0xffff0000 >> 16
		bDragging = true;
		SelectedVertex = pG->HitTest(mx, my, &U);
		if (bandera == 0)
		{
			bandera = 1;
			CVertex* pSource=U.CreateVertex(SelectedVertex);
			fuente = pSource->Key();
		}
		if (bandera == 2)
		{
			bandera = 3;
			CVertex* pDest = U.CreateVertex(SelectedVertex);
			destino = pDest->Key();
		}
		break;
	case WM_LBUTTONUP:
		if (bandera == 1)
			bandera = 2;
		if (bandera == 3)
			bandera = 4;
		bDragging = false;
		break;
	case WM_MOUSEMOVE:
		//if (bDragging)
		//{
			mx = LOWORD(lParam); // lParam&0x0000ffff;
			my = HIWORD(lParam); // lParam&0xffff0000 >> 16
			//InvalidateRect(hWnd, NULL, true);  // solo si el timer no actualiza la ventana
			//SelectedVertex = pG->HitTest(mx, my, &U);
		//}
		break;
	case WM_CREATE:
		SetTimer(hWnd, 1, 100, NULL);
		{
			fstream file;
			file.open("..\\Assets\\Graph1.txt");
			int nVertices;
			file >> nVertices;
			for (int i = 0; i < nVertices; i++)
			{
				long lID;
				float x, y;
				string strName;
				file >> lID >> x >> y >> strName;
				CVertex* V = U.CreateVertex(lID);
				// Comprobar si es un nodo especial
				if (strName == "costo")
				{
					vLog =V;
				}

				V->m_strName = strName;
				V->x = x;
				V->y = y;
				
				
			}
			int nEdges;
			file >> nEdges;
			pG = U.CreateGraph(0);
			for (int i = 0; i < nEdges; i++)
			{
				long left, right;
				file >> left >> right;
				CEdge* pE = U.CreateEdge(left, right);
				pG->ConnectWindow(left, right);
				//pG->Connect(left, right);
				//file >> left >> right;
			}
		}
		return 0;
	case WM_TIMER:
		switch (wParam)
		{
		case 1:
			fTime += 0.02;
			InvalidateRect(hWnd, NULL, true);
		}
		break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Analizar las selecciones de menú:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Agregar cualquier código de dibujo que use hDC aquí...

			//Ellipse(hdc, 10, 10, 100,100);
			//OJO DE MOSCA
			/*{
				const int nParts = 13;
				for (int i = 0; i < nParts; i++)
				{
					int x0, y0;
					x0 = 300 * sin(3*fTime)*cos(fTime + i * 2 * 3.141592f / nParts) + mx;
					y0 = 300 * cos(fTime)* sin(fTime + i * 2 * 3.141592f / nParts) + my;
					for (int j = 0; j < i;j++)
					{
						int x1, y1;
						x1 = 300 * sin(3 * fTime)*cos(fTime + j * 2 * 3.141592f / nParts) + mx;
						y1 = 300 * cos(fTime)*sin(fTime + j * 2 * 3.141592f / nParts) + my;
						MoveToEx(hdc, x0, y0, NULL);
						LineTo(hdc, x1, y1);
					}
				}
			}*/
			{
 				SetGraphicsMode(hdc, GM_ADVANCED);
				//Escala x3
				//XFORM W = { cos(fTime),-sin(fTime),sin(fTime),-cos(fTime),mx,my }
				XFORM W = { 1,0,0,1,0,0 };		// { m11(2) m12(0) eDx
												//   m21(0) m22(2) eDy
												//    0      0      1  }
				//	x' = x*M11 + y*M12 + eDx
				//	y' = x*M21 + y*M22 + eDy

				SetWorldTransform(hdc, &W);
			//	fstream pic;
			//	pic.open("..\\Descargas\\mapaCeti.png");
			//	HBRUSH fondo = CreatePatternBrush(_In_HBITMAP hbmp);
				if (pG)
				{
					pG->Draw(hdc, &U);
					if (SelectedVertex != -1&&bandera==2)
					{    //punto inicio
						HBRUSH RedBrush = CreateSolidBrush(RGB(254, 250, 10));
						SelectObject(hdc, RedBrush);
						CVertex* pV = U.CreateVertex(SelectedVertex);
						Ellipse(hdc, pV->x - 10, pV->y - 10, pV->x + 10, pV->y + 10);
						DeleteObject(RedBrush);
					}
					if (SelectedVertex != -1&&bandera==0)
					{
						HBRUSH RedBrush = CreateSolidBrush(RGB(254, 0, 0));
						SelectObject(hdc, RedBrush);
						CVertex* pV = U.CreateVertex(SelectedVertex);
						Ellipse(hdc, pV->x - 10, pV->y - 10, pV->x +10, pV->y + 10);
						DeleteObject(RedBrush);
					}
					if (destino!=-1&&destino!=fuente&&(bandera == 4||bandera==0))
					{
						bandera = 0;
						pS->ClearSearch(pG);
					/*	if (pS->DFS(pG, fuente, destino)) //Profundidad
						{
							list <long long> LEdges;
							int end = destino;
							long start;
							CVertex *Vertex;
							CEdge *Edge;
							while (end != fuente)
							{
								Vertex = U.CreateVertex(end);
								start = Vertex->GetParent();
								Edge = U.CreateEdge(start, end);
								end = start;
								LEdges.push_back(Edge->Key());
							}
							union { struct { long lFirst; long lSecond; }; long long llID; };
							CVertex *V1, *V2;
							while (start != destino)
							{
								llID = LEdges.back();
								LEdges.pop_back();
								end = lSecond;
								V1 = U.CreateVertex(lFirst);
								V2 = U.CreateVertex(lSecond);
								HPEN RedPEN = CreatePen(PS_SOLID, 5, RGB(254, 0, 0));
								SelectObject(hdc, RedPEN);
								MoveToEx(hdc, (int)V1->x, (int)V1->y, NULL);
								float pi = 3.14159265359;
								ARROWSTRUCT a = { 20,pi / 18,true };
								ArrowTo(hdc, (int)V2->x, (int)V2->y, &a);
								DeleteObject(RedPEN);
								start = end;
							}

						}
						else
						{
							HBRUSH RedBrush = CreateSolidBrush(RGB(250, 0, 0));
							SelectObject(hdc, RedBrush);
							CVertex* pV = U.CreateVertex(5);
							Ellipse(hdc, pV->x - 10, pV->y - 10, pV->x + 10, pV->y + 10);
							DeleteObject(RedBrush); 
						} 
						pS->ClearSearch(pG);
						if (pS->BFS(pG, fuente, destino)) //Amplitud 
						{
							list <long long> LEdges;
							int end = destino;
							long start;
							CVertex *Vertex;
							CEdge *Edge;
							while (end != fuente)
							{
								Vertex = U.CreateVertex(end);
								start = Vertex->GetParent();
								Edge = U.CreateEdge(start, end);
								end = start;
								LEdges.push_back(Edge->Key());
							}
							union { struct { long lFirst; long lSecond; }; long long llID; };
							CVertex *V1, *V2;
							while (start != destino)
							{
								llID = LEdges.back();
								LEdges.pop_back();
								end = lSecond;
								V1 = U.CreateVertex(lFirst);
								V2 = U.CreateVertex(lSecond);
								HPEN RedPEN = CreatePen(PS_SOLID, 5
									, RGB(250,0,0));
								SelectObject(hdc, RedPEN);
								MoveToEx(hdc, (int)V1->x, (int)V1->y, NULL);
								float pi = 3.14159265359;
								ARROWSTRUCT a = { 20,pi / 18,true };
								ArrowTo(hdc, (int)V2->x, (int)V2->y, &a);
								DeleteObject(RedPEN);
								start = end;
							}

						}
						else
						{
							HBRUSH RedBrush = CreateSolidBrush(RGB(250,0, 0));
							SelectObject(hdc, RedBrush);
							CVertex* pV = U.CreateVertex(2);
							Ellipse(hdc, pV->x - 10, pV->y - 10, pV->x + 10, pV->y + 10);
							DeleteObject(RedBrush);
						} */
						pS->ClearSearch(pG);
						if (pS->BF(pG, fuente, destino))//primero el mejor
						{
							list <long long> LEdges;
							int end = destino;
							long start;
							CVertex *Vertex;
							CEdge *Edge;
							while (end != fuente)
							{
								Vertex = U.CreateVertex(end);
								start = Vertex->GetParent();
								Edge = U.CreateEdge(start, end);
								end = start;
								LEdges.push_back(Edge->Key());
							}
							union { struct { long lFirst; long lSecond; }; long long llID; };
							CVertex *V1, *V2;
							while (start != destino)
							{
								llID = LEdges.back();
								LEdges.pop_back();
								end = lSecond;
								V1 = U.CreateVertex(lFirst);
								V2 = U.CreateVertex(lSecond);
								HPEN RedPEN = CreatePen(PS_SOLID, 6, RGB(0, 1000, 0));
								SelectObject(hdc, RedPEN);
								MoveToEx(hdc, (int)V1->x, (int)V1->y, NULL);
								float pi = 3.14159265359;
								ARROWSTRUCT a = { 20,pi / 18,true };
								ArrowTo(hdc, (int)V2->x, (int)V2->y, &a);
								DeleteObject(RedPEN);
								start = end;
								
							}

						}
						else
						{
							HBRUSH RedBrush = CreateSolidBrush(RGB(0, 0, 255));
							SelectObject(hdc, RedBrush);
							CVertex* pV = U.CreateVertex(2);
							Ellipse(hdc, pV->x - 10, pV->y - 10, pV->x + 10, pV->y + 10);
							DeleteObject(RedBrush);
						}

						pS->ClearSearch(pG);
						if (pS->HC(pG, fuente, destino)) //Acenso a la colina
						{
							list <long long> LEdges;
							int end = destino;
							long start;
							CVertex *Vertex;
							CEdge *Edge;
							while (end != fuente)
							{
								Vertex = U.CreateVertex(end);
								start = Vertex->GetParent();
								Edge = U.CreateEdge(start, end);
								end = start;
								LEdges.push_back(Edge->Key());
							}
							union { struct { long lFirst; long lSecond; }; long long llID; };
							CVertex *V1, *V2;
							while (start != destino)
							{
								llID = LEdges.back();
								LEdges.pop_back();
								end = lSecond;
								V1 = U.CreateVertex(lFirst);
								V2 = U.CreateVertex(lSecond);
								HPEN RedPEN = CreatePen(PS_SOLID, 3, RGB(1000, 0, 0));
								SelectObject(hdc, RedPEN);
								MoveToEx(hdc, (int)V1->x, (int)V1->y, NULL);
								float pi = 3.14159265359;
								ARROWSTRUCT a = { 20,pi / 18,true };
								ArrowTo(hdc, (int)V2->x, (int)V2->y, &a);
								DeleteObject(RedPEN);
								start = end;

								// Verificar si existe el nodo de log
								if(vLog != nullptr){
									vLog->m_strName = to_string(V2->cost);
								}
									
								//cout << V2->cost;
								
							}
						}
						else
						{
							HBRUSH RedBrush = CreateSolidBrush(RGB(0, 255, 0));
							SelectObject(hdc, RedBrush);
							CVertex* pV = U.CreateVertex(2);
							Ellipse(hdc, pV->x - 10, pV->y - 10, pV->x + 10, pV->y + 10);
							DeleteObject(RedBrush);
						}

					}
					//pG->Draw2(hdc, &U);
				}
				
			}
			//Flecha
			/*{
				float theta, pi = 3.14159265359;
				int Cx = 500, Cy = 250;
				ARROWSTRUCT a = { 10,30.0f,true };
				//a.nWidth = 10;
				//a.fTheta = 30.0f;
				//a.bFill = true;
				MoveToEx(hdc, Cx, Cy, NULL);
				if (mx > Cx && my<Cy)
				{
					theta = atan((my - Cy) / (mx - Cx));
				}
				if (mx < Cx && my > Cy)
				{
					theta = pi + atan((my - Cy) / (mx - Cx));
				}
				if (mx <= Cx && my <= Cy)
				{
					theta = pi + atan((my - Cy) / (mx - Cx));
				}
				if (mx >= Cx && my >= Cy)
				{
					theta = atan((my - Cy) / (mx - Cx));
				}
				mx1 = 200 * cos(theta);
				my1 = 200 * sin(theta);
				ArrowTo(hdc, Cx + mx1, Cy + my1, &a);
				//ArrowTo(hdc, mx, my, &a);
			}*/
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Controlador de mensajes del cuadro Acerca de.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}


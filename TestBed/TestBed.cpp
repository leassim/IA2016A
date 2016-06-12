// TestBed.cpp: define el punto de entrada de la aplicación de consola.
//

#include "stdafx.h"
#include "..\GraphLib\Vertex.h"
#include "..\GraphLib\Edge.h"
#include "..\GraphLib\GraphManager.h"
#include <fstream>
#include <iostream>
using namespace std;

int _tmain(int argc,_TCHAR* argv[])
{
	fstream file;
	file.open("..\\Assets\\Graph1.txt", ios::in);
	if (!file.is_open())
	{
		cout << "Error el archivo especificado no existe" << endl;
		return 0;
	}
	CGraphManager U;

	int nVertices, lID, nEdges, lFirst, lSecond, nGraph, IDGraph;
	file >> nVertices;
	for (int i = 0; i < nVertices; i++)
	{
		file >> lID;
		file >> U.CreateVertex(lID)->cost;
	   
	}
	//int nEdges, lFirst, lSecond, nGraph, IDGraph;
	file >> nEdges;
	for (int i = 0; i < nEdges; i++)

	{
		file >> lFirst >> lSecond;
		U.CreateEdge(lFirst, lSecond);
		//file.eof(); //Devuelve distinto de 0
	}
	
	/*file >> nGraph;
	for (int i = 0; i < nGraph; i++)
	{
		file >> IDGraph;
		U.CreateGraph(IDGraph);
		file >> nEdges;
		for (int it = 0; it < nEdges; it++)
		{
			file >> lFirst >> lSecond;
			U.CreateEdge(lFirst, lSecond);
			U.CreateGraph(IDGraph)->Connect(lFirst, lSecond);
		}
	}*/

	//auto v = U.CreateVertex(1);
	//auto p = U.CreateVertex(2);
	//auto e = U.CreateEdge(1, 2);
	//auto f = U.CreateEdge(2, 1);

    return 0;
}


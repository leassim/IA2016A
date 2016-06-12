#pragma once
#include "..\GraphLib\Vertex.h"
#include "..\GraphLib\Edge.h"
#include "..\GraphLib\Graph.h"
#include <map>
#include <set>
using namespace std;
//simbolos externos
class CVertex;
class CEdge;
class CGraph;

class CGraphManager
{
protected:
	
	map<long, CVertex*> m_mapVertex;
	map<long long, CEdge*> m_mapEdge;
	map<long, CGraph*>m_mapGraph;
public:

	CGraphManager();
	virtual ~CGraphManager();
	// Crea un vértice con el identificador especificado, si el vértice ya existe con ese ID, entonces se retorna la instancia previa.
	CVertex* CreateVertex(long lID);
	// Crea una arista con las claves de los vértices asociados.Si la aristaya existe, retorna la arista previa.
	CEdge* CreateEdge(long lIDFirst, long lIDSecond);
	/* Crea un grafo, si existe, retorna el existente */
	CGraph* CreateGraph(long lIDGraph);
	// //Destriur un grafo
	void DestroyGraph(long lIDGraph);
	void Clean();
};


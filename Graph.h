// Faisal Shaikh
// Fshaikh1
// PA4

#include "List.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


#ifndef PA4_GRAPH_H
#define PA4_GRAPH_H

#define white 0
#define grey 1
#define black -1

#define NIL -2
#define INF -3

typedef struct Graphobj* Graph;

/*** Constructors-Destructors ***/
Graph newGraph(int n);
void freeGraph(Graph* pG);
/*** Access functions ***/
int getOrder(Graph G);
int getSize(Graph G);
int getSource(Graph G);
int getParent(Graph G, int u);
int getDist(Graph G, int u);
void getPath(List L, Graph G, int u);
/*** Manipulation procedures ***/
void makeNull(Graph G);
void addEdge(Graph G, int u, int v);
void addArc(Graph G, int u, int v);
void BFS(Graph G, int s);
/*** Other operations ***/
void printGraph(FILE* out, Graph G);
void add(Graph G, List L, int x);

#endif //PA4_GRAPH_H

// Faisal Shaikh
#include<stdio.h>
#include <stdlib.h>
#include "List.h"
#include "Graph.h"

// Structs-------------------------------------------------------------------------------------------------------
typedef struct Graphobj
{
    // contains neighbors of vertex i
    List *adjacent;

    // ith element is the color of vertex i
    int *colors;

    // ith element is the parent of vertex i
    int *parent;

    // ith element is the distance from the most recent source to vertex i
    int *distance;

    // stores number of vertices
    int order;

    // stores the number of edges
    int size;

    // source of graph
    int source;
}Graphobj;

/*** Constructors-Destructors ***/
// creates new graph
Graph newGraph(int n)
{
    Graph G;
    G = malloc(sizeof(Graphobj));
    G->order = n;
    G->size = 0;
    G->source = NIL;

    // allocate memory for necessary graph fields
    G->adjacent = malloc((n+1) * sizeof(List));
    G->colors = malloc((n+1) * sizeof(int));
    G->parent = malloc((n+1) * sizeof(int));
    G->distance = malloc((n+1) * sizeof(int));

    // initialize graph field values
    for (int i = 1; i < n + 1; i++)
    {
        G->adjacent[i] = newList();
        G->colors[i] = white;
        G->parent[i] = NIL;
        G->distance[i] = INF;
    }
    return G;
}
// frees the graph
void freeGraph(Graph* pG)
{
    // traverse through graph and free adjacency elements
    for (int i = 1; i <= getOrder(*pG); i++)
    {
        freeList(&(*pG)->adjacent[i]);
    }
    // free remaining fields
    free((*pG)->adjacent);
    free((*pG)->colors);
    free((*pG)->parent);
    free((*pG)->distance);
    free(*pG);
    *pG = NULL;
}
/*** Access functions ***/
// returns vertices
int getOrder(Graph G)
{
    return G->order;
}
// returns edges
int getSize(Graph G)
{
    return G->size;
}
// returns source
int getSource(Graph G)
{
    return G->source;
}
// returns parent
int getParent(Graph G, int u)
{
    if(u < 1 || u > getOrder(G))
    {
        printf("Error: Graph out of bounds error");
        exit(1);
    }
    return G->parent[u];
}
// returns distance
int getDist(Graph G, int u)
{
    if(u < 1 || u > getOrder(G))
    {
        printf("Error: Graph out of bounds error");
        exit(1);
    }
    return G->distance[u];
}
// returns path recursively
void getPath(List L, Graph G, int u)
{
    if(getSource(G) == NIL)
    {
        printf("Error: Graph Source is NIL\n");
        exit(1);
    }
    if(u < 1 || u > getOrder(G))
    {
        printf("Error: Graph out of bounds error");
        exit(1);
    }
    if(G->source == u)
    {
        append(L, u);
    }
    else if(G->parent[u] == NIL || G->distance[u] == INF)
    {
        append(L, NIL);
    }
    else
    {
        getPath(L, G, G->parent[u]);
        append(L, u);
    }
}
/*** Manipulation procedures ***/
// clears graph
void makeNull(Graph G)
{
    G->size = 0;
    G->source = NIL;
    for (int i = 1; i <= getOrder(G); i++)
    {
        clear(G->adjacent[i]);
        G->colors[i] = white;
        G->parent[i] = NIL;
        G->distance[i] = INF;
    }
}
// adds edge (both ways)
void addEdge(Graph G, int u, int v)
{
    if(u < 1 || u > getOrder(G))
    {
        printf("Error: Graph out of bounds error1");
        exit(1);
    }
    if(v < 1 || v > getOrder(G))
    {
        printf("Error: Graph out of bounds error2");
        exit(1);
    }
    add(G, G->adjacent[u], v);
    add(G, G->adjacent[v], u);
    G->size++;
}
// adds arc (one way)
void addArc(Graph G, int u, int v)
{
    if(u < 1 || u > getOrder(G))
    {
        printf("Error: Graph out of bounds error");
        exit(1);
    }
    if(v < 1 || v > getOrder(G))
    {
        printf("Error: Graph out of bounds error");
        exit(1);
    }
    add(G, G->adjacent[u], v);
    G->size++;
}
// BFS algorithm
void BFS(Graph G, int s)
{
    for (int i = 1; i <= G->order; i++)
    {
        G->colors[i] = white;
        G->distance[i] = INF;
        G->parent[i] = NIL;
    }
    G->source = s;
    G->colors[s] = grey;
    G->distance[s] = 0;
    G->parent[s] = NIL;
    List queue = newList();
    append(queue, s);
    while (length(queue) != -0)
    {
        int i = front(queue);
        deleteFront(queue);
        for(moveFront(G->adjacent[i]); index(G->adjacent[i]) != -1; moveNext(G->adjacent[i]))
        {
            int j = get(G->adjacent[i]);
            if (G->colors[j] == white)
            {
                G->colors[j] = grey;
                G->distance[j] = G->distance[i] + 1;
                G->parent[j] = i;
                append(queue, j);
            }
        }
        G->colors[i] = black;
    }
    freeList(&queue);
}
/*** Other operations ***/
// prints graph
void printGraph(FILE* out, Graph G)
{
    for (int i = 1; i <= G->order; i++)
    {
        fprintf(out,"%d: ", i);
        printList(out, G->adjacent[i]);
        fprintf(out, "\n");
    }
}

// helper to insert edges and arcs
void add(Graph G, List L, int x)
{
    if(length(L) == 0)
    {
        append(L, x);
        return;
    }
    else if (length(L) > 0)
    {
        moveFront(L);
        while (index(L) != -1)
        {
            if (x < get(L))
            {
                insertBefore(L, x);
                return;
            }
            else if(x == get(L))
                G->size--;
            else
            {
                moveNext(L);
            }
        }

        if (index(L) == -1)
        {
            append(L, x);
            return;
        }
    }
}

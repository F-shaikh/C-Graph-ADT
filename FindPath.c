// Faisal Shaikh
#include "Graph.h"
#include "List.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


int main (int argc, char*argv[])
{
    FILE *in, *out;
    int i = 0; // vertices

    if (argc != 3)
    {
        printf("Usage: %s <input file> <output file>\n", argv[0]);
        exit(1);
    }

    // open files for reading and writing
    in = fopen(argv[1], "r");
    out = fopen(argv[2], "w");

    if (in == NULL)
    {
        printf("Unable to open file %s for reading\n", argv[1]);
        exit(1);
    }
    if (out == NULL)
    {
        printf("Unable to open file %s for writing\n", argv[2]);
        exit(1);
    }

    // begin graph
    fscanf(in, "%d", &i);
    Graph G = newGraph(i);
    int u = 0;
    int v = 0;
    int source = 0;
    int destination = 0;

    // fill graph
    int flag = 1;
    while (flag !=0)
    {
        fscanf(in, "%d %d", &u, &v);
        if(u == 0 && v == 0)
        {
            flag = 0;
            break;
        }
        addEdge(G,u,v);
    }
    printGraph(out, G);
    fprintf(out, "\n");

    // perform BFS
    List list = newList(); // new List
    int flagAgain = 1;
    while(flagAgain != 0)
    {
        fscanf(in, "%d %d", &source, &destination);
        if (source == 0 && destination == 0)
        {
            flagAgain = 0;
            break;
        }
        BFS(G, source);
        clear(list); // clears list to check next values from infile
        getPath(list, G, destination);
        moveFront(list);
        if (getDist(G, destination) != INF || getDist(G, destination) != 0) // case 1: dist is not INF or 0
        {
            fprintf(out,"The distance from %d to %d is %d\n", source, destination, length(list)-1);
            fprintf(out,"A shortest %d-%d path is: ", source, destination);
            printList(out, list);
            fprintf(out, "\n");
            fprintf(out, "\n");
        }
        else if (source == destination) // case 2: if the source and destination are the same
        {
            printf("source is: %d    Dest is: %d\n", source, destination);
            fprintf(out, "The distance from %d to %d is\n", source, destination);
            fprintf(out, "A shortest path %d-%d is: %d\n", source, destination, source);
            printList(out, list);
            fprintf(out, "\n");
            fprintf(out, "\n");
        }
        else // case 3: if the distance is infinity, or anything else
        {
            fprintf(out, "The distance from %d to %d is infinity\n", source, destination);
            fprintf(out, "No %d-%d path exists\n", source, destination);
            fprintf(out, "\n");
        }

    }
    // free everything at the end and close files
    freeList(&list);
    freeGraph(&G);
    fclose(in);
    fclose(out);
    return (0);
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"

#define SIZE 1024

struct graph* loadGraph(char *filename);
int lines(char *filename);
void contract_rth_edge(struct graph* graph, int r);


char *filename = "kargerMinCut.txt";


int main()
{
    int v = lines(filename);
    int mincut = v*v;

    srand(0); // seed rand()

    for (int i = 0; i < v*v; i++)
    {
        struct graph* graph = loadGraph(filename);
        if (graph == NULL)
        {
            fprintf(stderr, "Graph failed to load\n");
            return 1;
        }
        while(graph->vc > 2)
        {
            //printGraph(graph);
            //printf("vertices left: %i\n", graph->vc);
            contract_rth_edge(graph, rand());
        }
        if (graph->m < mincut)
        {
            mincut = graph->m;
        }
        if (i%v == 0)
        {
            printf("i = %d\n", i);
            printf("m = %d\n", graph->m);
            printf("2 * mincut = %d\n\n", mincut);
        }
    }
    printf("FINAL ANSWER:  2 * MINCUT = %d\n\n",mincut);
}

//create graph from .txt adjacency list
struct graph* loadGraph(char *filename)
{

    int v = lines(filename);
    char line[SIZE], *token;
    char delims[] = " \t\r\n";
    int vertex, adj, tokenIsRead;
    struct graph* newGraph = createGraph(v);

    FILE* file = fopen(filename,"r");
    while(fgets(line, SIZE, file) != NULL)
    {
        // adapted from https://stackoverflow.com/questions/31522555/read-int-with-scanf-until-new-line

        // read vertex
        token = strtok(line, delims);
        //printf("%s\n",token);
        tokenIsRead = sscanf(token, "%d", &vertex);
        //printf("Vertex: %d\n",vertex);


        // read first adjacent
        token = strtok(NULL, delims);
        //printf("%s\n",token);
        tokenIsRead = sscanf(token, "%d", &adj);
        //printf("Adj: %d\n",adj);

        while(tokenIsRead > 0)
        {
            addAdj(newGraph, vertex - 1, adj - 1);
            newGraph->m += 1;
            token = strtok(NULL, delims);
            if (token == NULL)
            {
                break;
            }
            tokenIsRead = sscanf(token, "%d", &adj);
        }
    }
    fclose(file);
    return newGraph;
}

// get number of lines in file
int lines(char *filename)
{
    FILE* file = fopen(filename,"r");
    int lines = 0;
    char ch;
    while (!feof(file))
    {
        ch = fgetc(file);
        if(ch == '\n')
        {
            lines++;
        }
    }
    fclose(file);
    return lines;
}

void contract_rth_edge(struct graph* graph, int r)
{
    int v1 = 0;// origin vertex
    int v2 = 0;// adj vertex

    r = (r%(graph->m)) + 1; // r must be integer s.t. 1 <= r <= (2 * total edges)

    //cycle through vertices until found vertex with rth edge
    while (r > graph->vertices[v1].d)
    {
        r -= graph->vertices[v1].d;
        v1 += 1;
    }
    //cycle through edges until found rth edge
    struct adjListNode *next = graph->vertices[v1].head;
    for (int i = 1; i < r; i++)
    {
        next = next->next;
    }
    v2 = next->val;

    if (v1 == v2)
    {
        printf("Found self-loop at vertex %d.\n",v1);
    }

    //make v1 < v2
    if (v1 > v2)
    {
        int temp = v1;
        v1 = v2;
        v2 = temp;
    }

    //printf("contracting vertices %i and %i", v1, v2);

    contract(graph, v1, v2);
}

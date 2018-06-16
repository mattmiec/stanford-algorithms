#include <stdlib.h>
#include <stdio.h>

//define node for linked list of integers
struct adjListNode
{
    int val; // adjacent vertex
    struct adjListNode* next;
};

struct adjList
{
    int d; // degree of vertex
    struct adjListNode* head;
};

struct graph
{
    int v; // initial number of vertices, does not change with contractions
    int vc; // number of connected vertices, decreases by 1 with each contraction
    int m; // 2 * total number of edges
    struct adjList* vertices;
};

struct graph* createGraph(int v)
{
    struct graph* graph = malloc(sizeof(struct graph));
    graph->v = v;
    graph->vc = v;
    graph->m = 0;
    graph->vertices = malloc( v * sizeof(struct adjList) );
    for (int i = 0; i < v; i++)
    {
        graph->vertices[i].d = 0;
        graph->vertices[i].head = NULL;
    }
    return graph;
}

void addAdj(struct graph* graph, int v1, int v2)
{
    //list v2 as adjacent to v1
    struct adjListNode* newNode1 = malloc(sizeof(struct adjListNode));
    newNode1->val = v2;
    newNode1->next = graph->vertices[v1].head;
    graph->vertices[v1].d += 1;
    graph->vertices[v1].head = newNode1;
}

void printGraph(struct graph* graph)
{
    int verifym = 0;
    for (int i = 0; i < graph->v; i++)
    {
        int verifyd = 0;
        printf("%d:", i + 1);
        struct adjListNode *next = graph->vertices[i].head;
        while (next != NULL)
        {
            verifym += 1;
            verifyd += 1;
            printf(" %d", next->val + 1);
            next = next->next;
        }
        printf("\n");
        if (verifyd != graph->vertices[i].d)
        {
            printf("ERROR: PRINTED %d EDGES FOR d = %d AT VERTEX %d.\n\n" , verifyd, graph->vertices[i].d, i);
        }
        else
        {
            printf("d = %d\n\n", verifyd);
        }
    }
    if (verifym != graph->m)
    {
        printf("ERROR: PRINTED TOTAL %d(/2) EDGES FOR m = %d.\n\n", verifym, graph->m);
    }
    else
    {
        printf("m = %d\n\n\n", verifym);
    }
}

void contract(struct graph* graph, int v1, int v2)
// add adjacency list of v2 to v1 then "remove" v2
{
    // printf("contracting v1 = %d and v2 = %d\n",v1,v2);
    // loop over v1's adjacency list and remove edge to v2 (preemptively remove self-loops)
    struct adjListNode **next_v1 = &(graph->vertices[v1].head);
    struct adjListNode *next;
    while (*next_v1 != NULL)
    {
        if ((*next_v1)->val == v2)
        {
                next = *next_v1;
                *next_v1 = (*next_v1)->next;
                free(next);
                graph->vertices[v1].d -= 1;
                graph->m -= 1;
        }
        else
        {
            next_v1 = &((*next_v1)->next);
        }
    }

    // loop over v2's adjacency list
    struct adjListNode *next_v2 = graph->vertices[v2].head;
    while (next_v2 != NULL)
    {
        int v3 = next_v2->val;
        // if not self-loop
        if (!(v3 == v1))
        {
            // add edge to v1's adjacency list
            addAdj(graph, v1, v3);
            graph->m += 1;

            // v2 becomes v1 in v3's adjacency list
            struct adjListNode *next_v3 = graph->vertices[v3].head;
            while (next_v3 != NULL)
            {
                if (next_v3->val == v2)
                {
                    next_v3->val = v1;
                }
                next_v3 = next_v3->next;
            }
        }

        // move to next node in v2's adjacency list, free current node
        struct adjListNode *current = next_v2;
        next_v2 = next_v2->next;
        free(current);
        graph->m -= 1;
        graph->vertices[v2].d -= 1;
        //printf("v2 remaining edges: %d\n", graph->vertices[v2].d);
        //printf("total current edges: %d\n", graph->m);
    }

    // v2 is now disconnected
    graph->vertices[v2].head = NULL;
    graph->vc -= 1;

}


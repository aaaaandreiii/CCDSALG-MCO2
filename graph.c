#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"


// Create a new node
Node* createNode(char *name) {
    Node *newNode = (Node *)malloc(sizeof(Node));  // Explicitly cast the result of malloc to Node*
    newNode->name = strdup(name);
    newNode->next = NULL;
    return newNode;
}

// Get the index of the vertex
int getVertexIndex(Graph *graph, char *name) {
    int i;
    for (i = 0; i < graph->numVertices; i++) {
        if (graph->adjLists[i] && strcasecmp(graph->adjLists[i]->name, name) == 0) {  // Use strcasecmp for case-insensitive comparison
            return i;
        }
    }
    return -1; // Return -1 if vertex is not found
}

// Create a graph with a specified number of vertices
Graph* createGraph(int vertices) {
    Graph *graph = (Graph *)malloc(sizeof(Graph));  // Explicitly cast the result of malloc to Graph*
    graph->numVertices = vertices;
    graph->adjLists = (Node **)malloc(vertices * sizeof(Node *));  // Explicitly cast the result of malloc to Node**
    graph->visited = (int *)malloc(vertices * sizeof(int));  // Explicitly cast the result of malloc to int*

    int i;
    for (i = 0; i < vertices; i++) {
        graph->adjLists[i] = NULL;
        graph->visited[i] = 0;
    }

    return graph;
}

// Add an edge to the graph
void addEdge(Graph *graph, char *src, char *dest) {
    int srcIndex = getVertexIndex(graph, src);
    int destIndex = getVertexIndex(graph, dest);

    // Ensure valid indices
    if (srcIndex == -1 || destIndex == -1) {
        return; // Skip adding edge if vertex is invalid
    }

    // Add dest to the adjacency list of src
    Node *newNode = createNode(dest);
    if (graph->adjLists[srcIndex] == NULL) {
        graph->adjLists[srcIndex] = newNode;
    } else {
        Node *temp = graph->adjLists[srcIndex];
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }

    // Add src to the adjacency list of dest
    newNode = createNode(src);
    if (graph->adjLists[destIndex] == NULL) {
        graph->adjLists[destIndex] = newNode;
    } else {
        Node *temp = graph->adjLists[destIndex];
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}



// Print the graph
void printGraph(Graph *graph) {
    int v;
    for (v = 0; v < graph->numVertices; v++) {
        Node *temp = graph->adjLists[v];
        printf("\n Vertex %s\n: ", temp->name);
        while (temp) {
            printf("%s -> ", temp->name);
            temp = temp->next;
        }
        printf("\n");
    }
}

// Free the graph memory
void freeGraph(Graph *graph) {
    int i; // Declare the loop variable
    for (i = 0; i < graph->numVertices; i++) {
        Node *temp = graph->adjLists[i];
        while (temp) {
            Node *toFree = temp;
            temp = temp->next;
            free(toFree->name);
            free(toFree);
        }
    }
    free(graph->adjLists);
    free(graph->visited);
    free(graph);
}


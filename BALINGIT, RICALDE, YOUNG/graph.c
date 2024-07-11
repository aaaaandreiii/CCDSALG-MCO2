#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"

Node* createNode(char *name) {
    Node *newNode = malloc(sizeof(Node));
    newNode->name = strdup(name);
    newNode->next = NULL;
    return newNode;
}

Graph* createGraph(int vertices) {
    Graph *graph = malloc(sizeof(Graph));
    graph->numVertices = vertices;

    graph->adjLists = malloc(vertices * sizeof(Node *));
    graph->visited = malloc(vertices * sizeof(int));

    int i;
    for (i = 0; i < vertices; i++) {
        graph->adjLists[i] = NULL;
        graph->visited[i] = 0;
    }

    return graph;
}

void addEdge(Graph *graph, char *src, char *dest) {
    int srcIndex = getVertexIndex(graph, src);
    int destIndex = getVertexIndex(graph, dest);

    Node *newNode = createNode(dest);
    newNode->next = graph->adjLists[srcIndex];
    graph->adjLists[srcIndex] = newNode;

    newNode = createNode(src);
    newNode->next = graph->adjLists[destIndex];
    graph->adjLists[destIndex] = newNode;
}

int getVertexIndex(Graph *graph, char *name) {
    int i;
    for (i = 0; i < graph->numVertices; i++) {
        if (graph->adjLists[i] && strcmp(graph->adjLists[i]->name, name) == 0) {
            return i;
        }
    }
    return -1;
}

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

void freeGraph(Graph *graph) {
    int v;
    for (v = 0; v < graph->numVertices; v++) {
        Node *temp = graph->adjLists[v];
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

void BFS(Graph *graph, char *startVertex, FILE *outputFile) {
    int startIndex = getVertexIndex(graph, startVertex);
    if (startIndex == -1) {
        fprintf(stderr, "Vertex %s not found.\n", startVertex);
        return;
    }

    int queue[graph->numVertices];
    int front = 0;
    int rear = 0;

    graph->visited[startIndex] = 1;
    queue[rear++] = startIndex;

    while (front != rear) {
        int currentIndex = queue[front++];
        fprintf(outputFile, "%s ", graph->adjLists[currentIndex]->name);

        Node *temp = graph->adjLists[currentIndex];
        while (temp) {
            int adjIndex = getVertexIndex(graph, temp->name);
            if (graph->visited[adjIndex] == 0) {
                graph->visited[adjIndex] = 1;
                queue[rear++] = adjIndex;
            }
            temp = temp->next;
        }
    }

    fprintf(outputFile, "\n");
}

void DFSUtil(Graph *graph, char *vertex, FILE *outputFile) {
    int vertexIndex = getVertexIndex(graph, vertex);
    graph->visited[vertexIndex] = 1;
    fprintf(outputFile, "%s ", vertex);

    Node *temp = graph->adjLists[vertexIndex];
    while (temp) {
        int adjIndex = getVertexIndex(graph, temp->name);
        if (graph->visited[adjIndex] == 0) {
            DFSUtil(graph, temp->name, outputFile);
        }
        temp = temp->next;
    }
}

void DFS(Graph *graph, char *startVertex, FILE *outputFile) {
    int startIndex = getVertexIndex(graph, startVertex);
    if (startIndex != -1) {
        DFSUtil(graph, startVertex, outputFile);
        fprintf(outputFile, "\n");
    } else {
        fprintf(stderr, "Vertex %s not found.\n", startVertex);
    }
}


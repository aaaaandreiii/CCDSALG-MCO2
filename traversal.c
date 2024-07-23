#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// BFS traversal
void BFS(Graph *graph, char *startVertex, FILE *outputFile) {
    int startIndex = getVertexIndex(graph, startVertex);
    if (startIndex == -1) {
        fprintf(stderr, "Vertex %s not found.\n", startVertex);
        return;
    }

    int queue[graph->numVertices];
    int front = 0;
    int rear = 0;
    int i; // Declare the loop variable outside the loop

    // Reset the visited array before BFS traversal
    for (i = 0; i < graph->numVertices; i++) {
        graph->visited[i] = 0;
    }

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

// DFS traversal proper
void DFS(Graph *graph, char *vertex, FILE *outputFile) {
    int vertexIndex = getVertexIndex(graph, vertex);
    graph->visited[vertexIndex] = 1;
    fprintf(outputFile, "%s ", vertex);

    Node *temp = graph->adjLists[vertexIndex];
    while (temp) {
        int adjIndex = getVertexIndex(graph, temp->name);
        if (graph->visited[adjIndex] == 0) {
            DFS(graph, temp->name, outputFile);
        }
        temp = temp->next;
    }
}

// DFS traversal initialization
void DFSInit(Graph *graph, char *startVertex, FILE *outputFile) {
    int startIndex = getVertexIndex(graph, startVertex);
    int i; // Declare the loop variable outside the loop

    if (startIndex != -1) {
        // Reset the visited array before DFS traversal
        for (i = 0; i < graph->numVertices; i++) {
            graph->visited[i] = 0;
        }
        DFS(graph, startVertex, outputFile);
    } else {
        fprintf(stderr, "Vertex %s not found.", startVertex);
    }
}

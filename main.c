#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.c"
#include "traversal.c"



//Main.C
void readGraphFromFile(Graph *graph, const char *filename, int *fileExists) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "%s not found.\n", filename);
        *fileExists = 0;
        return;
    }

    *fileExists = 1;
    char buffer[256];
    int vertices;
    int i;
    fscanf(file, "%d", &vertices);

    for (i = 0; i < vertices; i++) {
        fscanf(file, "%s", buffer);
        graph->adjLists[i] = createNode(buffer);

        while (fscanf(file, "%s", buffer) && strcmp(buffer, "-1") != 0) {
            addEdge(graph, graph->adjLists[i]->name, buffer);
        }
    }

    fclose(file);
}

void writeTraversalsToFile(Graph *graph, const char *filename, char *startVertex) {
    FILE *outputFile = fopen(filename, "w");
    if (!outputFile) {
        fprintf(stderr, "Error opening file %s for writing.\n", filename);
        return;
    }

    int i;
    for (i = 0; i < graph->numVertices; i++) {
        Node *temp = graph->adjLists[i];
        int degree = 0;
        while (temp->next) {
            degree++;
            temp = temp->next;
        }
        // Fix degree calculation: exclude self and -1
        fprintf(outputFile, "%s %d\n", graph->adjLists[i]->name, degree);
    }
    fprintf(outputFile, "\n");

    // Ensure visited array is reset before BFS and DFS traversals
    for (i = 0; i < graph->numVertices; i++) {
        graph->visited[i] = 0;
    }
    BFS(graph, startVertex, outputFile);
    fprintf(outputFile, "\n");

    for (i = 0; i < graph->numVertices; i++) {
        graph->visited[i] = 0;
    }
    DFSInit(graph, startVertex, outputFile);
    fprintf(outputFile, "\n");

    fclose(outputFile);
}

int main() {
    char inputFilename[256], startVertex[256];
    int fileExists = 1;

    printf("Input filename: ");
    scanf("%s", inputFilename);
    printf("Input start vertex for the traversal: ");
    scanf("%s", startVertex);

    FILE *file = fopen(inputFilename, "r");
    if (file) {
        int numVertices;
        fscanf(file, "%d", &numVertices);
        fclose(file);

        Graph *graph = createGraph(numVertices);
        readGraphFromFile(graph, inputFilename, &fileExists);

        if (fileExists && getVertexIndex(graph, startVertex) != -1) {
            writeTraversalsToFile(graph, "TRAVERSALS.TXT", startVertex);
        } else {
            fprintf(stderr, "Vertex %s not found.\n", startVertex);
        }

        freeGraph(graph);
    } else {
        fprintf(stderr, "%s not found.\n", inputFilename);
    }

    return 0;
}
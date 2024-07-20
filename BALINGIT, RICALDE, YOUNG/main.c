#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Graph.H
typedef struct Node {
    char *name;
    struct Node *next;
} Node;

typedef struct Graph {
    int numVertices;
    Node **adjLists;
    int *visited;
} Graph;

//Graph.C
// Create a new node
Node* createNode(char *name) {
    Node *newNode = (Node *)malloc(sizeof(Node));  // Explicitly cast the result of malloc to Node*
    newNode->name = strdup(name);
    newNode->next = NULL;
    return newNode;
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






//Traversal.C
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

// DFS utility function
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

// DFS traversal
void DFS(Graph *graph, char *startVertex, FILE *outputFile) {
    int startIndex = getVertexIndex(graph, startVertex);
    int i; // Declare the loop variable outside the loop

    if (startIndex != -1) {
        // Reset the visited array before DFS traversal
        for (i = 0; i < graph->numVertices; i++) {
            graph->visited[i] = 0;
        }
        DFSUtil(graph, startVertex, outputFile);
    } else {
        fprintf(stderr, "Vertex %s not found.", startVertex);
    }
}







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
    DFS(graph, startVertex, outputFile);
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
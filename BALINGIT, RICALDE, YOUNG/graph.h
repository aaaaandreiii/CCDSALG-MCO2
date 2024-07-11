#ifndef GRAPH_H
#define GRAPH_H

typedef struct Node {
    char *name;
    struct Node *next;
} Node;

typedef struct Graph {
    int numVertices;
    Node **adjLists;
    int *visited;
} Graph;

// Function prototypes
Graph* createGraph(int vertices);
void addEdge(Graph *graph, char *src, char *dest);
void printGraph(Graph *graph);
void freeGraph(Graph *graph);

void BFS(Graph *graph, char *startVertex, FILE *outputFile);
void DFS(Graph *graph, char *startVertex, FILE *outputFile);
void DFSUtil(Graph *graph, char *vertex, FILE *outputFile);

Node* createNode(char *name);
int getVertexIndex(Graph *graph, char *name);

#endif


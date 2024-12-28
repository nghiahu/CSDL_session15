#include <stdio.h>
#include <stdlib.h>
#define MAX 100


typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

typedef struct Graph {
    Node* adjList[MAX];
    int numVertices;
} Graph;

Graph* createGraph(int vertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = vertices;

    for (int i = 0; i < vertices; i++) {
        graph->adjList[i] = NULL;
    }
    return graph;
}

void addEdge(Graph* graph, int src, int dest) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = dest;
    newNode->next = graph->adjList[src];
    graph->adjList[src] = newNode;
}

int DFS(Graph* graph, int vertex, int* visited, int* recStack) {
    visited[vertex] = 1;
    recStack[vertex] = 1;

    Node* temp = graph->adjList[vertex];
    while (temp) {
        int adjVertex = temp->vertex;
        if (!visited[adjVertex]) {
            if (DFS(graph, adjVertex, visited, recStack)) {
                return 1; 
            }
        }
        else if (recStack[adjVertex]) {
            return 1; 
        }
        temp = temp->next;
    }
    recStack[vertex] = 0;
    return 0; 
}
int hasCycle(Graph* graph) {
    int visited[MAX] = {0};
    int recStack[MAX] = {0};

    for (int i = 0; i < graph->numVertices; i++) {
        if (!visited[i]) {
            if (DFS(graph, i, visited, recStack)) {
                return 1;
            }
        }
    }
    return 0; 
}

int main() {
    int V, E;
    printf("Nhap so dinh (V) va so canh (E): ");
    scanf("%d %d", &V, &E);

    Graph* graph = createGraph(V);

    printf("Nhap danh sach cac canh (u, v):\n");
    for (int i = 0; i < E; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        addEdge(graph, u, v);
    }

    if (hasCycle(graph)) {
        printf("Do thi co chu trinh\n");
    } else {
        printf("Do thi khong co chu trinh\n");
    }

    for (int i = 0; i < V; i++) {
        Node* temp = graph->adjList[i];
        while (temp) {
            Node* toFree = temp;
            temp = temp->next;
            free(toFree);
        }
    }
    free(graph);

    return 0;
}

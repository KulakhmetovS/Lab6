#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int** Creategraph(int **, int);

int size;

// <---------- Список смежности ---------->
struct node
{
    int vertex;
    struct node* next;
};
struct node* createNode(int);
struct Graph
{
    int numVertices;
    struct node** adjLists;
};
struct Graph* createGraph(int vertices);
void addEdge(struct Graph* graph, int src, int dest);
void printGraph(struct Graph* graph);
// <---------- ! ---------->


int **VertexIdentification(int **, int, int, int);
int **EdgeContraction(int **, int, int, int);
int **SplitVertex(int **, int, int);


int main()
{
    int i, j, num;
    int **graph = NULL, **graphClone = NULL, **Graph = NULL;

    printf("\t# Graphs #\n\n");
    printf("Enter the number of graph vertices (positive integer): ");
    scanf("%d", &size);
    num = size - 1;

    // Creating the graph
    graph = Creategraph(graph, size);
    graphClone = Creategraph(graphClone, size);

    // Printing the matrix
    for(i = 0; i < size; i++)
    {
        for(j = 0; j < size; j++)
        {
            printf("%d ", graph[i][j]);
            graphClone[i][j] = graph[i][j];
        }
        printf("\n");
    }


// <---------- Список смежности ---------->
    struct Graph* graf = createGraph(size);

    for(i = 0; i < size; i++)
    {
        for(j = i; j < size; j++)
        {
            if(graph[i][j] == 1)
            {
                addEdge(graf, i, j);
            }
        }
    }

    printf("\n# Adjacency list #\n");
    printGraph(graf);

    int vertex1, vertex2;
    printf("Enter the number of graph vertices (positive integer) you need identify: ");
    scanf("%d%d", &vertex1, &vertex2);

    Graph = VertexIdentification(graph, size, vertex1, vertex2);

    for(i = 0; i < size - 1; i++)
    {
        for(j = 0; j < size - 1; j++)
            printf("%d ", Graph[i][j]);
        printf("\n");
    }
    printf("\n");

    for(i = 0; i < size; i++)
        for(j = 0; j < size; j++)
            graph[i][j] = graphClone[i][j];


    Graph = NULL, vertex1 = 0, vertex2 = 0;

    printf("Enter the number of graph vertices (positive integer) whose edge need to be contracted: ");
    scanf("%d%d", &vertex1, &vertex2);

    for(i = 0; i < size; i++)
    {
        if((graphClone[vertex1][i] == 1) && (i == vertex2)) goto contraction;
    }
    printf("edge does not exist\n");
goto end;

contraction:
    Graph = EdgeContraction(graphClone, size, vertex1, vertex2);

    for(i = 0; i < size - 1; i++)
    {
        for(j = 0; j < size - 1; j++)
            printf("%d ", Graph[i][j]);
        printf("\n");
    }
    printf("\n");

end:
    printf("Enter the number of graph vertices (positive integer) you need split: ");
    scanf("%d", &vertex1);
    Graph = SplitVertex(graph, size, vertex1);

    for(i = 0; i < size + 1; i++)
    {
        for(j = 0; j < size + 1; j++)
            printf("%d ", Graph[i][j]);
        printf("\n");
    }

    free(graphClone);
    free(Graph);
    free(graph);

    return 0;
}


int** Creategraph(int **graph, int size)
{
    srand(time(NULL));

    int i = 0, j = 0;

    // Memory allocation
    graph = (int **)(malloc(sizeof(int *) * size));
    for(i = 0; i < size; i++)
        graph[i] = (int *)(malloc(sizeof(int *) * size));

    // Filling the matrix
    for(i = 0; i < size; i++)
        for(j = i; j < size; j++)
        {
            graph[i][j] = rand() % 2;
            graph[j][i] = graph[i][j];
            if(i == j) graph[i][j] = 0;
            if(graph[i][j] == 1);
        }

    return graph;
}


// <---------- Список смежности ---------->
struct node* createNode(int v)
{
    struct node* newNode = malloc(sizeof(struct node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

struct Graph* createGraph(int vertices)
{
    struct Graph* graph = malloc(sizeof(struct Graph));
    graph->numVertices = vertices;

    graph->adjLists = malloc(vertices * sizeof(struct node*));

    int i;
    for (i = 0; i < vertices; i++)
        graph->adjLists[i] = NULL;

    return graph;
}

void addEdge(struct Graph* graph, int src, int dest)
{
    // Add edge from src to dest
    struct node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    // Add edge from dest to src
    newNode = createNode(src);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}

void printGraph(struct Graph* graph)
{
    int v;
    for (v = 0; v < graph->numVertices; v++)
    {
        struct node* temp = graph->adjLists[v];
        printf("%d:  ", v);
        while (temp)
        {
            printf("%d ", temp->vertex);
            temp = temp->next;
        }
        printf("\n");
    }
}

int **VertexIdentification(int **graph, int size, int vertex1 , int vertex2)
{
    int res = 0, val1, val2, i, j;
    int **Graph = NULL;

    Graph = (int **)(malloc(sizeof(int *) * (size - 1)));
    for(i = 0; i < size - 1; i++)
        Graph[i] = (int *)(malloc(sizeof(int *) * (size - 1)));

    // ---------- logical addition of strings ----------
    for(i = 0; i < size; i++)
    {
        //graph[vertex1][i] || graph[vertex2][i];
        val1 = graph[vertex1][i];
        val2 = graph[vertex2][i];

        __asm(
        "movl %[val1], %%eax\n\t"
        "movl %[val2], %%ebx\n\t"
        "orl %%ebx, %%eax\n\t"
        :"=a" (res)
        :[val1] "m" (val1), [val2] "m" (val2)
        :"cc"
        );

        graph[vertex2][i] = res;
    }

    for(i = 0; i < size; i++)
    {
        val1 = graph[i][vertex1];
        val2 = graph[i][vertex2];

        __asm(
        "movl %[val1], %%eax\n\t"
        "movl %[val2], %%ebx\n\t"
        "orl %%ebx, %%eax\n\t"
        :"=a" (res)
        :[val1] "m" (val1), [val2] "m" (val2)
        :"cc"
        );

        graph[i][vertex2] = res;
    }

    for (i  = vertex1; i < size - 1; i++)
        for (j = 0; j < size; j++)
            graph[i][j] = graph[i + 1][j];

    for (i = 0; i < size; i++)
        for (j = vertex1; j < size - 1; j++)
            graph[i][j] = graph[i][j + 1];

    for (i = 0; i < size - 1; i++)
        for (j = 0; j < size - 1; j++)
            Graph[i][j] = graph[i][j];

    return Graph;
}

int **EdgeContraction(int **graph, int size, int vertex1 , int vertex2)
{
    int **Graph = NULL;
    Graph = (int **)(malloc(sizeof(int *) * (size - 1)));

    Graph = VertexIdentification(graph, size, vertex1, vertex2);

    for(int i = 0; i < size - 1; i++)
        for(int j = 0; j < size - 1; j++)
                if(i == j) Graph[i][j] = 0;

    return Graph;
}

int **SplitVertex(int **graph, int size, int vertex)
{
    int i, j;
    int **Graph = NULL;

    Graph = (int **)(malloc(sizeof(int *) * (size + 1)));
    for(i = 0; i < size + 1; i++)
        Graph[i] = (int *)(malloc(sizeof(int *) * (size + 1)));


    for(i = 0; i < size; ++i)
        for(j = 0; j < size; ++j)
            Graph[i][j] = graph[i][j];

    for(i = 0; i < size; ++i)
    {
        Graph[i][size] = graph[i][vertex];
        Graph[size][i] = graph[vertex][i];
    }

    Graph[vertex][size] = 1;
    Graph[size][vertex] = 1;

    return Graph;
}

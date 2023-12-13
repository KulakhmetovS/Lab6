#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int** Creategraph(int **, int);

void GraphUnion(int **, int**, int, int);
int **GraphIntersection(int **, int**, int);
int **GraphXOR(int **, int**, int);
void PrintGraph(int **, int);

int main()
{
    int i, j, size1, size2;
    int **graph1 = NULL, **graph2 = NULL, **Graph = NULL;

    printf("\t# Graphs #\n\n");


    // Creating the graph
    printf("Enter the number of first graph vertices (positive integer): ");
    scanf("%d", &size1);
    graph1 = Creategraph(graph1, size1);

    printf("Enter the number of second graph vertices (positive integer): ");
    scanf("%d", &size2);
    graph2 = Creategraph(graph2, size2);

    // Printing the matrix
    for(i = 0; i < size1; i++)
    {
        for(j = 0; j < size1; j++)
        {
            printf("%d ", graph1[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    for(i = 0; i < size2; i++)
    {
        for(j = 0; j < size2; j++)
        {
            printf("%d ", graph2[i][j]);
        }
        printf("\n");
    }

    GraphUnion(graph1, graph2, size1, size2);

    /*
    printf("Graphs union\n");

    if(size1 > size2) PrintGraph(Graph, size1);
    else PrintGraph(Graph, size2);


    for(i = 0; i < size; i++)
        free(Graph[i]);
    free(Graph);

    Graph = GraphIntersection(graph1, graph2, size);

    printf("Graphs intersection\n");
    PrintGraph(Graph, size);

    for(i = 0; i < size; i++)
        free(Graph[i]);
    free(Graph);

    Graph = GraphXOR(graph1, graph2, size);

    printf("Ring sum of graphs\n");
    PrintGraph(Graph, size);

    free(Graph);
    for(i = 0; i < size; i++)
        free(graph1[i]);
    free(graph1);
    for(i = 0; i < size; i++)
        free(graph2[i]);
    free(graph2);
    */
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

void GraphUnion(int **graph1, int** graph2, int size1, int size2)
{
    printf("\n# Graph union #");

    int **Graph = NULL;
    int res, val1, val2, size_max, size_min;

    if(size1 > size2)
    {
        size_max = size1;
        size_min = size2;
    }
    else
    {
        size_max = size2;
        size_min = size1;
    }

    Graph = (int **)(malloc(sizeof(int *) * size_max));
    for(int i = 0; i < size_max; i++)
        Graph[i] = (int *)(malloc(sizeof(int *) * size_max));

    if(size_max == size1)
    {
    for(int i = 0; i < size_max; i++)
        for(int j = 0; j < size_max; j++)
            Graph[i][j] = graph1[i][j];
    }
    else
    {
    for(int i = 0; i < size_max; i++)
    for(int j = 0; j < size_max; j++)
        Graph[i][j] = graph2[i][j];
    }

    for(int i = 0; i < size_min; i++)
        for(int j = 0; j < size_min; j++)
            {
                if(size_max == size1) val1 = graph2[i][j];
                else val1 = graph1[i][j];

                val2 = Graph[i][j];
                __asm(
                        "movl %[val2], %%eax\n\t"
                        "movl %[val1], %%ebx\n\t"
                        "orl %%ebx, %%eax\n\t"
                        :"=a" (res)
                        :[val1] "m" (val1), [val2] "m" (val2)
                        :"cc"
                        );

                Graph[i][j] = res;
            }

    printf("\n");
    PrintGraph(Graph, size_max);
}

int **GraphIntersection(int **graph1, int**graph2, int size)
{
    int **Graph = NULL;
    int res, val1, val2;

    Graph = (int **)(malloc(sizeof(int *) * size));
    for(int i = 0; i < size; i++)
        Graph[i] = (int *)(malloc(sizeof(int *) * size));

    for(int i = 0; i < size; i++)
        for(int j = 0; j < size; j++)
            Graph[i][j] = graph2[i][j];

    for(int i = 0; i < size; i++)
        for(int j = 0; j < size; j++)
            {
                val1 = graph1[i][j];
                val2 = Graph[i][j];
                __asm(
                        "movl %[val2], %%eax\n\t"
                        "movl %[val1], %%ebx\n\t"
                        "andl %%ebx, %%eax\n\t"
                        :"=a" (res)
                        :[val1] "m" (val1), [val2] "m" (val2)
                        :"cc"
                        );

                Graph[i][j] = res;
            }

    return Graph;
}

int **GraphXOR(int **graph1, int **graph2, int size)
{
    int **Graph = NULL;
    int res, val1, val2;

    Graph = (int **)(malloc(sizeof(int *) * size));
    for(int i = 0; i < size; i++)
        Graph[i] = (int *)(malloc(sizeof(int *) * size));

    for(int i = 0; i < size; i++)
        for(int j = 0; j < size; j++)
            Graph[i][j] = graph2[i][j];

    for(int i = 0; i < size; i++)
        for(int j = 0; j < size; j++)
            {
                val1 = graph1[i][j];
                val2 = Graph[i][j];
                __asm(
                        "movl %[val2], %%eax\n\t"
                        "movl %[val1], %%ebx\n\t"
                        "xorl %%ebx, %%eax\n\t"
                        :"=a" (res)
                        :[val1] "m" (val1), [val2] "m" (val2)
                        :"cc"
                        );

                Graph[i][j] = res;
            }

    return Graph;
}

void PrintGraph(int **Graph, int size)
{
    for(int i = 0; i < size; i++)
    {
        for(int j = 0; j < size; j++)
        {
            printf("%d ", Graph[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    for(int i = 0; i < size; i++)
        free(Graph[i]);
}

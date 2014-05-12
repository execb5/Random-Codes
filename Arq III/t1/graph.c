#include<stdio.h>
#include<stdlib.h>
#include<LinkedList.h>

#define MAX 1000

typedef struct
{
	bool matrixAdj[MAX][MAX];
	List* list;
} Graph;

typedef struct
{
	int val;
	List* neighbors;
} GraphNode;

void insertArc(Graph* graph, int i, int j)
{
	graph->matrixAdj[i][j] = true;
}

void insertNode(Graph* graph, int val)
{
	GraphNode* ptr = (GraphNode*) malloc(sizeof(GraphNode));
	if (ptr == NULL)
	{
		printf("\n GraphNode creation failed. \n");
		return;
	}
	ptr->val = val;
	ptr->neighbors = NULL;
	graph->list->head = addToList(graph->list, ptr, true);
}

int main(int argc, const char *argv[])
{
	Graph g;
	int i = 0;
	while (i < 10)
	{
		insertNode(&g, i);
		i++;
	}
	print(g.list);
	return 0;
}

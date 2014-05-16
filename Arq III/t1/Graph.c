#include<stdio.h>
#include<stdlib.h>
#include<LinkedList.h>

#define MAX 3000
#define SEED 1

unsigned char graph[MAX][MAX];
unsigned char marks[MAX];
//int graph[MAX][MAX];
//int marks[MAX];
List nodes;
unsigned int sum;

void crazyPath(int node)
{
	if (marks[node])
	{
		return;
	}
	marks[node] = 1;
	int i = 0;
	for (i = 0; i < MAX; i++)
	{
		if (graph[node][i])
		{
			sum += getVal(&nodes, i);
			crazyPath(i);
		}
	}
}

int main(int argc, const char *argv[])
{
	srand(SEED);
	nodes.head = NULL;
	nodes.current = NULL;
	nodes.size = 0;
	sum = 0;
	int i = 0;
	int j = 0;
	printf("\nGenerating connections...");
	for (i = 0; i < MAX; i++)
	{
		for (j = 0; j < MAX; j++)
		{
			graph[j][i] = rand() % 2;
		}
		marks[i] = 0;
		//printf(".");
		nodes.head = addToList(&nodes, rand() % MAX, true);
	}
	printf("DONE!!\n");
	printf("\nStarting crazyPath...");
	crazyPath(0);
	printf("DONE!!\n");
	destroy(&nodes);
	printf("Sum = %d\n", sum);
	return 0;
}

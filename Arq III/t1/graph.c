#include<stdio.h>
#include<stdlib.h>
#include<LinkedList.h>

#define MAX 100

bool matrixAdj[MAX][MAX];
List list;

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

void insertNode(int val)
{
	
}

int main(int argc, const char *argv[])
{
	
	return 0;
}

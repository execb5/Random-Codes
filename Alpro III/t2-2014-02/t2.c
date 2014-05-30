#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
	unsigned char** connections;
	unsigned char* grey;
	unsigned char* black;
	int size;
} Graph;

int getEquivalent(int* vet, int num)
{
	if (vet[num] == -1)
		return num;
	return getEquivalent(vet, vet[num]);
}

Graph* readFile(const char filename[])
{
	FILE *file = fopen(filename, "r");
	char* pch;
	if (file != NULL)
	{
		char line[128];
		fgets(line, sizeof line, file);
		int num = atoi(line);

		printf("Number of connections: %d\n", num);

		int nodes[2][num];
		int node;
		int equalsSize = 2*num;
		int equals[equalsSize];
		int graphSize = 0;

		//Initialize arrays with -1.
		int i;
		for (i = 0; i < num; i++)
			nodes[0][i] = nodes[1][i] = -1;
		for (i = 0; i < equalsSize; i++)
			equals[i] = -1;

		int cont = 0;
		while (fgets(line, sizeof line, file) != NULL)
		{
			line[strlen(line)-1] = '\0';
			pch = strtok(line, " ");
			while (pch != NULL)
			{
				node = atoi(pch);
				pch = strtok(NULL, " ");
				switch (*(pch))
				{
					case '<':
						pch = strtok(NULL, " ");
						nodes[0][cont] = node;
						nodes[1][cont] = atoi(pch);
						if (nodes[0][cont] > graphSize)
							graphSize = nodes[0][cont];
						if (nodes[1][cont] > graphSize)
							graphSize = nodes[1][cont];
						pch = strtok(NULL, " ");
						break;
					case '>':
						pch = strtok(NULL, " ");
						nodes[1][cont] = node;
						nodes[0][cont] = atoi(pch);
						if (nodes[0][cont] > graphSize)
							graphSize = nodes[0][cont];
						if (nodes[1][cont] > graphSize)
							graphSize = nodes[1][cont];
						pch = strtok(NULL, " ");
						break;
					case '=':
						pch = strtok(NULL, " ");
						equals[atoi(pch)] = node;
						pch = strtok(NULL, " ");
						break;

				}
			}
			cont++;
		}
		fclose(file);

		//Print the arrays on the screen.
		printf("[ ");
		for (i = 0; i < cont; i++)
			printf("%d ", nodes[0][i]);
		printf("]\n");
		printf("[ ");
		for (i = 0; i < cont; i++)
			printf("%d ", nodes[1][i]);
		printf("]\n");
		printf("[ ");
		for (i = 0; i < equalsSize; i++)
			printf("%d ", equals[i]); 
		printf("]\n");

		printf("Graph's size: %d\n", graphSize);
		printf("19 is equal to: %d\n", getEquivalent(equals, 19));

		int j;
		unsigned char matrix[graphSize][graphSize];

		//Initialize matrix
		for (i = 0; i < graphSize; i++)
			for (j = 0; j < graphSize; j++)
				matrix[i][j] = 0;

		//Fill the graph with connections
		int a;
		int b;
		for (i = 0; i < cont; i++)
		{
			if (nodes[0][cont] != -1)
			{
				a = getEquivalent(equals, nodes[0][i]);
				b = getEquivalent(equals, nodes[1][i]);
				matrix[a][b] = 1;
			}
		}

		//Print graph
		printf("    ");
		for (i = 0; i < graphSize; i++)
			printf("%*d ", 2, i);
		printf("\n    ");
		for (i = 0; i < graphSize; i++)
			printf("%*c ", 2, '_');
		printf("\n");
		for (i = 0; i < graphSize; i++)
		{
			printf("%*d[ ", 2, i);
			for (j = 0; j < graphSize; j++)
				printf("%*d ", 2, matrix[i][j]);
			printf("]\n");
		}

		Graph graph;
		graph.connections = matrix;

	}
	else
	{
		perror(filename);
	}
}

int main(int argc, const char *argv[])
{
	static const char filename[] = "casosTeste/ex001";
	readFile(filename);
	return 0;
}

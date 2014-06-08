#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int SIZE = 0;
int SOURCE_NODES = 0;



int* getSourceNodes(unsigned char (*matrix)[SIZE])
{
	int i;
	int j;
	unsigned char isSource;
	unsigned char sources[SIZE];

	//Initialize sources
	for (i = 0; i < SIZE; i++) {
		sources[i] = 0;
	}

	for (i = 0; i < SIZE; i++)
	{
		isSource = 1;
		for (j = 0; j < SIZE && isSource == 1; j++)
		{
			if (matrix[j][i])
			{
				isSource = 0;
			}
		}
		if (isSource == 1)
		{
			sources[SOURCE_NODES] = i;
			SOURCE_NODES++;
		}
	}
	return sources;
}

int maxInt(unsigned char (*matrix)[SIZE], unsigned char* black, unsigned char* grey, unsigned char* values)
{
	int* sources = getSourceNodes(matrix);
	int i;
	printf("[ ");
	for (i = 0; i < SOURCE_NODES; i++) {
		printf("%d ", sources[i]);
	}
	printf("]\n");
	return 0;
}

int getEquivalent(int* vet, int num)
{
	if (vet[num] == -1)
		return num;
	return getEquivalent(vet, vet[num]);
}

void testFile(const char filename[])
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
		int i;
		int j;

		//Initialize nodes and equals with -1.
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
						if (nodes[0][cont] > SIZE)
							SIZE = nodes[0][cont];
						if (nodes[1][cont] > SIZE)
							SIZE = nodes[1][cont];
						pch = strtok(NULL, " ");
						break;
					case '>':
						pch = strtok(NULL, " ");
						nodes[1][cont] = node;
						nodes[0][cont] = atoi(pch);
						if (nodes[0][cont] > SIZE)
							SIZE = nodes[0][cont];
						if (nodes[1][cont] > SIZE)
							SIZE = nodes[1][cont];
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
			printf("%*d ", 2, nodes[0][i]);
		printf("]\n");
		printf("[ ");
		for (i = 0; i < cont; i++)
			printf("%*d ", 2, nodes[1][i]);
		printf("]\n");
		printf("[ ");
		for (i = 0; i < equalsSize; i++)
			printf("%*d ", 2, equals[i]); 
		printf("]\n");

		printf("Graph's size: %d\n", SIZE);
		printf("19 is equal to: %d\n", getEquivalent(equals, 19));

		unsigned char matrix[SIZE][SIZE];
		unsigned char grey[SIZE];
		unsigned char black[SIZE];
		unsigned char values[SIZE];

		//Initialize matrix and other arrays
		for (i = 0; i < SIZE; i++)
		{
			for (j = 0; j < SIZE; j++)
				matrix[i][j] = 0;
			values[i] = black[i] = grey[i] = 0;
		}

		//Fill the graph with connections
		int a;
		int b;
		for (i = 0; i < cont; i++)
		{
			if (nodes[0][i] != -1)
			{
				a = getEquivalent(equals, nodes[0][i]);
				b = getEquivalent(equals, nodes[1][i]);
				printf("Adding connection from %d to %d.\n", a, b);
				matrix[a][b] = 1;
			}
		}

		//Print graph
		printf("    ");
		for (i = 0; i < SIZE; i++)
			printf("%*d ", 2, i);
		printf("\n    ");
		for (i = 0; i < SIZE; i++)
			printf("%*c ", 2, '_');
		printf("\n");
		for (i = 0; i < SIZE; i++)
		{
			printf("%*d[ ", 2, i);
			for (j = 0; j < SIZE; j++)
				printf("%*d ", 2, matrix[i][j]);
			printf("]\n");
		}

		int result = maxInt(matrix, black, grey, values);

	}
	else
	{
		perror(filename);
	}
}

int main(int argc, const char *argv[])
{
	static const char filename[] = "casosTeste/ex001";
	testFile(filename);
	return 0;
}

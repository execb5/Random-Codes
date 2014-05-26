#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
	unsigned char** connections;
	int* values;
	int size;
} Graph;

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

		int nodes1[num];
		int nodes2[num];
		char relation[num];

		int cont = 0;
		while (fgets(line, sizeof line, file) != NULL)
		{
			line[strlen(line)-1] = '\0';
			pch = strtok(line, " ");
			while (pch != NULL)
			{
				nodes1[cont] = atoi(pch);
				pch = strtok(NULL, " ");
				relation[cont] = *pch;
				pch = strtok(NULL, " ");
				nodes2[cont] = atoi(pch);
				pch = strtok(NULL, " ");
			}
			cont++;
		}
		fclose(file);

		//Print the arrays on the screen.
		int i;
		printf("[ ");
		for (i = 0; i < num; i++)
			printf("%d ", nodes1[i]);
		printf("]\n");
		printf("[ ");
		for (i = 0; i < num; i++)
			printf("%c ", (relation[i]));
		printf("]\n");
		printf("[ ");
		for (i = 0; i < num; i++)
			printf("%d ", nodes2[i]);
		printf("]\n");

		int size = 0;
		for (i = 0; i < num; i++)
		{
			if (nodes1[i] > size)
				size = nodes1[i];
			if (nodes2[i] > size)
				size = nodes2[i];
		}
		printf("%d\n", size);

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

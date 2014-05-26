#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void readFile(const char filename[])
{
	FILE *file = fopen(filename, "r");
	unsigned char state = 0;
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
				switch (state)
				{
					case 0:
						nodes1[cont] = atoi(pch);
						pch = strtok(NULL, " ");
						state = 1;
						break;
					case 1:
						relation[cont] = *pch;
						pch = strtok(NULL, " ");
						state = 2;
						break;
					case 2:
						nodes2[cont] = atoi(pch);
						pch = strtok(NULL, " ");
						state = 0;
						break;
				}
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

		int size;
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

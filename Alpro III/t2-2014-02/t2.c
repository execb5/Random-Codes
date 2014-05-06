#include <stdio.h>
#include <string.h>

int main(int argc, const char *argv[])
{
	static const char filename[] = "casosTeste/ex001";
	FILE *file = fopen(filename, "r");
	char* pch;
	if (file != NULL)
	{
		char line[128]; 
		while (fgets(line, sizeof line, file) != NULL)
		{
			line[strlen(line)-1] = '\0';
			pch = strtok(line, " ");
			while (pch != NULL)
			{
				printf("%s\n", pch);
				pch = strtok(NULL, " ");
			}
		}
		fclose(file);
	}
	else
	{
		perror(filename);
	}
	return 0;
}

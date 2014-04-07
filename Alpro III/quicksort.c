#include<stdio.h>

void swap(int* x, int* b)
{
	int aux;

	aux = *x;
	*x = *b;
	*b = aux;
}

int separate(int* vet, int value, int end)
{
	int pivot = vet[value];
	int i = value;
	int j = value + 1;

	while(j < end)
	{
		if(vet[j] < pivot)
		{
			i++;
			swap(&vet[i], &vet[j]);
		}
		j++;
	}
	swap(&vet[value], &vet[i]);

	return i;
}

void quicksort(int* vet, int i, int j)
{
	int separation;

	if(i < j)
	{
		separation = separate(vet, i, j);
		quicksort(vet, i, separation);
		quicksort(vet, separation + 1, j);
	}
}

int main()
{
	int vet[] = {40, 50, 33, 43, 89, 10, 20, 44, 65, 1, 10, 43, 124, 120};
	int size = sizeof(vet)/sizeof(int);

	int i = 0;
	printf("[ ");
	while(i < size)
	{
		printf("%d ", vet[i]);
		i++;
	}
	printf("]\n");

	quicksort(vet, 0, size);

	i = 0;
	printf("\n[ ");
	while(i < size)
	{
		printf("%d ", vet[i]);
		i++;
	}
	printf("]\n");
}

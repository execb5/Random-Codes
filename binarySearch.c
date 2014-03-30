#include<stdio.h>

int binarySearch(int x, int vet[], int m, int n)
{
	int middle = (m + n)/2;
	if(vet[middle] == x)
		return middle;
	if(x > vet[middle])
		return binarySearch(x, vet, middle + 1, n);
	if(x < vet[middle])
		return binarySearch(x, vet, m, middle - 1);
	return -1;
}

int main()
{
	int i, size, x;
	int vet[100];
	printf("Tell me the size that you want, max is 100.");
	scanf("%d", &size);
	printf("Enter the numbers in ascending order: \n");
	i = 0;
	while(i < size)
	{
		scanf("%d", &vet[i]);
		i++;
	}
	printf("Enter the number to be found: ");
	scanf("%d", &x);
	printf("The position is: %d\n", binarySearch(x, vet, 0, size-1));
	return 0;
}

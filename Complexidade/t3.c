/*
 * Nomes: Matthias Nunes e Gabriel Carlos
 * Complexidade e Otimização de Algoritmos
 * T3
*/

#include<stdio.h>
#include<stdlib.h>
#include<LinkedList.h>

void algoritmo(int soma, int metade, int tamanho, List* partition1, List* partition2, List* listaDeNumeros, int index)
{
	if (soma > metade)
		return;
	if (soma == metade)
	{
		printf("---------------------------------------------\n");
		print(partition1);
		print(partition2);
		printf("---------------------------------------------\n");
		return;
	}

	int i;
	int val;
	List copySet1;
	List copySet2;
	for (i = index; i < tamanho; i++)
	{
		copySet1 = copy(partition1);
		copySet2 = copy(partition2);
		val = getVal(listaDeNumeros, i);
		copySet1.head = addToList(&copySet1, val, true);
		del(&copySet2, val);
		algoritmo(soma + val, metade, tamanho, &copySet1, &copySet2, listaDeNumeros, ++index);
		destroy(&copySet1);
		destroy(&copySet2);
	}
	
}

int main(int argc, const char *argv[])
{
	int i;
	int soma = 0;
	int tamanho = argc - 1;

	List list;
	initializeList(&list);

	for (i = 1; i < argc; i++)
	{
		list.head = addToList(&list, atoi(argv[i]), true);
		soma += atoi(argv[i]);
	}
	
	printf("Conjunto: ");
	print(&list);

	if (soma%2 == 0)
	{
		int metade = soma / 2;
		if (max(&list) <= metade)
		{
			List partition1;
			initializeList(&partition1);
			List partition2;
			partition2 = copy(&list);
			algoritmo(0, metade, tamanho, &partition1, &partition2, &list, 0);
			destroy(&list);
			destroy(&partition1);
			destroy(&partition2);
		}
		else
		{
			printf("Não foi encontrado\n");
			destroy(&list);
		}

	}
	else
	{
		printf("Não foi encontrado\n");
		destroy(&list);
	}
	return 0;
}

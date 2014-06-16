/*
 * Nomes: Matthias Nunes e Gabriel Carlos
 * Complexidade e Otimização de Algoritmos
 * T3
 *
 * PARA VER O ALGORITMO DIRETO, SÓ PULAR PARA A LINHA 191
*/

#include<stdio.h>
#include<stdlib.h>

/*********************DECLARAÇÔES******************************************************************/

typedef enum {false, true} bool;

struct Node
{
	int val;
	struct Node* next;
};

typedef struct
{
	struct Node* head;
	struct Node* current;
	int size;
} List;

int qtdResult = 0;

/*********************INÍCIO LINKED LIST************************************************************/

void initializeList(List* list)
{
	list->head = NULL;
	list->current = NULL;
	list->size = 0;
}

struct Node* createList(List* list, int val)
{
	//printf("\n Creating a list with headnode as [%d]\n", val);

	struct Node* ptr = (struct Node*) malloc(sizeof(struct Node));
	if (ptr == NULL)
	{
		printf("\n Node creation failed. \n");
		return NULL;
	}
	ptr->val = val;
	ptr->next = NULL;

	list->head = list->current = ptr;
	list->size++;
	return list->head;
}

struct Node* addToList(List* list, int val, bool addToEnd)
{
	if (list->head == NULL)
		return createList(list, val);
	
	struct Node* ptr = (struct Node*) malloc(sizeof(struct Node));
	if (ptr == NULL)
	{
		//printf("\n Node creation failed. \n");
		return NULL;
	}
	ptr->val = val;
	ptr->next = NULL;

	if (addToEnd)
	{
		//printf("\n Adding node to the end of the list with value of [%d] \n", val);
		list->current->next = ptr;
		list->current = ptr;
	}
	else
	{
		//printf("\n Adding node to the beginning of the list with value of [%d] \n", val);
		ptr->next = list->head;
		list->head = ptr;
	}

	list->size++;
	return list->head;
}

bool deleteAux(List* list, int val, struct Node* node, struct Node* prev)
{
	if (node == NULL) 
		return false;
	if (node->val == val)
	{
		if (prev == NULL)
		{
			//printf("\n Deleting node with value of [%d] \n", val);
			struct Node* tmp = list->head;
			list->head = list->head->next;
			free(tmp);
			list->size--;
			return true;
		}
		//printf("\n Deleting node with value of [%d] \n", val);
		prev->next = node->next;
		free(node);
		list->size--;
		return true;
	}
	return deleteAux(list, val, node->next, prev = node);
}

bool del(List* list, int val)
{
	return deleteAux(list, val, list->head, NULL);
}

void printAux(struct Node* node)
{
	if (node == NULL)
		return;
	printf("%d ", node->val);
	printAux(node->next);
}

void print(List* list)
{
	printf("[ ");
	printAux(list->head);
	printf("]\n");
}

int getVal(List* list, int index)
{
	struct Node* ptr = list->head;
	int cont = 0;
	while (ptr != NULL)
	{
		if (cont == index)
			return ptr->val;
		cont++;
		ptr = ptr->next;
	}
	return -1;
}

List copy(List* list)
{
	List lst;
	initializeList(&lst);
	int i = 0;
	while (i < list->size)
	{
		lst.head = addToList(&lst, getVal(list, i), true);
		i++;
	}
	return lst;
}

void destroyAux(struct Node* node)
{
	if (node == NULL)
		return;
	destroyAux(node->next);
	//printf("Freeing node with the value of %d\n", node->val);
	free(node);
}

void destroy(List* list)
{
	destroyAux(list->head);
}

int maxAux(struct Node* node)
{
	if (node == NULL)
		return -1;
	int maybeMax = maxAux(node->next);
	return node->val > maybeMax ? node->val : maybeMax;
}

int max(List* list)
{
	return maxAux(list->head);
}

/***************FIM LINKED LIST********************************************************************/

/***************TRABALHO DE COMPLEXIDADE***********************************************************/

void algoritmo(int soma, int metade, int tamanho, List* partition1, List* partition2, List* listaDeNumeros, int index)
{
	if (soma > metade)
		return;
	if (soma == metade)
	{
		qtdResult++;
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
		algoritmo(soma + val, metade, tamanho, &copySet1, &copySet2, listaDeNumeros, i + 1);
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
			int val = getVal(&list, 0);
			partition1.head = addToList(&partition1,  val, true);
			List partition2;
			partition2 = copy(&list);
			del(&partition2, val);
			algoritmo(0 + val, metade, tamanho, &partition1, &partition2, &list, 1);
			destroy(&list);
			destroy(&partition1);
			destroy(&partition2);
			printf("Quantidade de resultados: %d\n", qtdResult);
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

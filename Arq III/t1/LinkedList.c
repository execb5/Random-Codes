#include<LinkedList.h>

struct Node* createList(List* list, void* data)
{
	struct Node* ptr = (struct Node*) malloc(sizeof(struct Node));
	if (ptr == NULL)
	{
		printf("\n Node creation failed. \n");
		return NULL;
	}
	ptr->data = data;
	ptr->next = NULL;

	list->head = list->current = ptr;
	list->size++;
	return list->head;
}

struct Node* addToList(List* list, void* data, bool addToEnd)
{
	if (list->head == NULL)
		return createList(list, data);
	
	struct Node* ptr = (struct Node*) malloc(sizeof(struct Node));
	if (ptr == NULL)
	{
		printf("\n Node creation failed. \n");
		return NULL;
	}
	ptr->data = data;
	ptr->next = NULL;

	if (addToEnd)
	{
		list->current->next = ptr;
		list->current = ptr;
	}
	else
	{
		ptr->next = list->head;
		list->head = ptr;
	}

	list->size++;

	return list->head;
}


void* getData(List* list, int index)
{
	struct Node* ptr = list->head;
	int cont = 0;
	while (ptr != NULL)
	{
		if (cont == index)
			return ptr->data;
		cont++;
		ptr = ptr->next;
	}
	return NULL;
}

void destroyAux(struct Node* node)
{
	if (node == NULL)
		return;
	destroyAux(node->next);
	free(node);
}

void destroy(List* list)
{
	destroyAux(list->head);
}

/*
bool deleteAux(List* list, int val, struct Node* node, struct Node* prev)
{
	if (node == NULL) 
		return false;
	if (node->val == val)
	{
		if (prev == NULL)
		{
			struct Node* tmp = list->head;
			list->head = list->head->next;
			free(tmp);
			return true;
		}
		prev->next = node->next;
		free(node);
		return true;
	}
	return deleteAux(list, val, node->next, prev = node);
}

bool del(List* list, int val)
{
	return deleteAux(list, val, list->head, NULL);
}
*/

/*
void printAux(struct Node* node)
{
	if (node == NULL)
		return;
	printf("%d ", node->data);
	printAux(node->next);
}

void print(List* list)
{
	printf("[ ");
	printAux(list->head);
	printf("]\n");
}
*/

/*
int main(int argc, const char *argv[])
{
	List list;
	list.head = NULL;
	list.current = NULL;
	int i = 0;
	while (i < 5)
	{
		list.head = addToList(&list, &i, false);
		i++;
	}
	print(&list);
	printf("%d\n", getVal(&list, 1));
	printf("%d\n", list);
	destroy(&list);
	printf("%d\n", list);
	return 0;
}
*/

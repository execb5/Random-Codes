#include<LinkedList.h>

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
	lst.head = NULL;
	lst.current = NULL;
	lst.size = 0;
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

/*
int main(int argc, const char *argv[])
{
	List list;
	list.head = NULL;
	list.current = NULL;
	list.size = 0;
	int i = 0;
	while (i < 10)
	{
		list.head = addToList(&list, i, false);
		i++;
	}
	print(&list);
	printf("Size: %d\n\n", list.size);
	i = 0;
	while (i < 3)
	{
		del(&list, i + 2);
		i++;
	}
	print(&list);
	printf("Size: %d\n\n", list.size);
	printf("list[5]: %d\n", getVal(&list, 5));
	List cp = copy(&list);
	printf("Original\n");
	print(&list);
	printf("Copy\n");
	print(&cp);
	destroy(&list);
	destroy(&cp);
	return 0;
}
*/

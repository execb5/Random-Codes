#include<LinkedList.h>

struct Node* createList(int val)
{
	printf("\n Creating a list with headnode as [%d]\n", val);

	struct Node* ptr = (struct Node*) malloc(sizeof(struct Node));
	if (ptr == NULL)
	{
		printf("\n Node creation failed. \n");
		return NULL;
	}
	ptr->val = val;
	ptr->next = NULL;

	head = current = ptr;
	return ptr;
}

struct Node* addToList(int val, bool addToEnd)
{
	if (head == NULL)
		return createList(val);
	
	struct Node* ptr = (struct Node*) malloc(sizeof(struct Node));
	if (ptr == NULL)
	{
		printf("\n Node creation failed. \n");
		return NULL;
	}
	ptr->val = val;
	ptr->next = NULL;

	if (addToEnd)
	{
		printf("\n Adding node to the end of the list with value of [%d] \n", val);
		current->next = ptr;
		current = ptr;
	}
	else
	{
		printf("\n Adding node to the beginning of the list with value of [%d] \n", val);
		ptr->next = head;
		head = ptr;
	}

	return ptr;
}

bool searchAux(int val, struct Node* node)
{
	if (node == NULL)
		return false;
	if (node->val == val)
		return true;
	return searchAux(val, node->next);
}

bool search(int val)
{
	return searchAux(val, head);
}

bool deleteAux(int val, struct Node* node, struct Node* prev)
{
	if (node == NULL) 
		return false;
	if (node->val == val)
	{
		if (prev == NULL)
		{
			struct Node* tmp = head;
			head = head->next;
			free(tmp);
			return true;
		}
		prev->next = node->next;
		free(node);
		return true;
	}
	return deleteAux(val, node->next, prev = node);
}

bool del(int val)
{
	return deleteAux(val, head, NULL);
}

void printAux(struct Node* node)
{
	if (node == NULL)
		return;
	printf("%d ", node->val);
	printAux(node->next);
}

void print()
{
	printf("[ ");
	printAux(head);
	printf("]\n");
}

int sizeAux(struct Node* node)
{
	if (node == NULL)
		return 0;
	return sizeAux(node->next) + 1;
}

int size()
{
	return sizeAux(head);
}

int getVal(int index)
{
	struct Node* ptr = head;
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

int main(int argc, const char *argv[])
{
	struct Node* list = NULL;
	int i = 0;
	while (i < 5)
	{
		addToList(i, true);
		i++;
	}
	printf("There is a 4 in the list? %d\n", search(4));
	printf("There is a 5 in the list? %d\n", search(5));
	printf("What is in position 3 in the list? %d\n", getVal(3));
	printf("Size of the list? %d\n", size());
	print();
	printf("%d\n", del(3));
	print();
	printf("Size of the list? %d\n", size());
	printf("Did I delete the 1 in the list? %d\n", del(1));
	print();
	del(0);
	del(2);
	del(4);
	print();
	return 0;
}
#include<stdio.h>

typedef enum {false, true} bool;

struct Node
{
	int val;
	struct Node* next;
};

struct Node* head = NULL;
struct Node* current = NULL;

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

struct Node* searchAux(int val, struct Node* node)
{
	if (node == NULL)
		return NULL;
	if (node->val == val)
		return node;
	return searchAux(val, node->next);
}

struct Node* search(int val)
{
	return searchAux(val, head);
}

bool deleteAux(int val)
{
	struct Node* del = search(val);

	if (del == NULL)
		return false;
	else
	{
	}
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
	printf("There is a 4 on the list? %d\n", search(4));
	printf("There is a 5 on the list? %d\n", search(5));
	return 0;
}

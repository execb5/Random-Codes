#include<stdio.h>
#include<stdlib.h>

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
	unsigned long size;
} List;

struct Node* head = NULL;
struct Node* current = NULL;

struct Node* createList(List* list, int val);
struct Node* addToList(List* list, int val, bool addToEnd);
bool deleteAux(List* list, int val, struct Node* node, struct Node* prev);
bool del(List* list, int val);
void printAux(struct Node* node);
void print(List* list);
int getVal(List* list, int index);
List copy(List* list);

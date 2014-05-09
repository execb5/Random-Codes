#include<stdio.h>
#include<stdlib.h>

typedef enum {false, true} bool;

struct Node
{
	int val;
	struct Node* next;
};

struct Node* head = NULL;
struct Node* current = NULL;

struct Node* createList(int val);
struct Node* addToList(int val, bool addToEnd);
bool searchAux(int val, struct Node* node);
bool search(int val);
bool deleteAux(int val, struct Node* node, struct Node* prev);
bool del(int val);
void printAux(struct Node* node);
void print();

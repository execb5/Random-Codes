#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include<stdio.h>
#include<stdlib.h>

typedef enum {false, true} bool;

typedef struct
{
	struct Node* head;
	struct Node* current;
	int size;
} List;

struct Node
{
	void* data;
	struct Node* next;
};

struct Node* createList(List* list, void* data);
struct Node* addToList(List* list, void* data, bool addToEnd);
void* getData(List* list, int index);
void destroyAux(struct Node* node);
void destroy(List* list);
//bool deleteAux(List* list, int val, struct Node* node, struct Node* prev);
//bool del(List* list, int val);
void printAux(struct Node* node);
void print(List* list);

#endif

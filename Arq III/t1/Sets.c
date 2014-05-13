#include<stdio.h>
#include<stdlib.h>
#include<LinkedList.h>

//gera(S, S')
//	se S estiver vazio
//		imprime S'
//	rnd = rnd
//	lista Z = list S sem o rnd
//	gera(Z, S')
//	Lista Z'= list S' com o rnd
//	gera(Z, Z')

void subSets(List* S, List* Z)
{
	if (S->size == 0)
	{
		print(Z);
		destroy(S);
		destroy(Z);
	}
	//int rnd = rand() % S->size;
	int rnd = 0;

	int value = getVal(S, rnd);

	List SS = copy(S);
	List ZZ = copy(Z);
	List ZZZ = copy(Z);

	destroy(S);
	destroy(Z);

	del(&SS, value);
	ZZZ.head = addToList(&ZZ, value, true);

	subSets(&SS, &ZZ);

	subSets(&SS, &ZZZ);
}

int main(int argc, const char *argv[])
{
	srand(time(NULL));

	List list;
	list.head = NULL;
	list.current = NULL;
	list.size = 0;

	int i = 0;
	while (i < 5)
	{
		list.head = addToList(&list, i, true);
		i++;
	}

	List empty;
	empty.head = NULL;
	empty.current = NULL;
	empty.size = 0;

	printf("List : ");
	print(&list);
	printf("Empty: ");
	print(&empty);
	subSets(&list, &empty);

	return 0;
}

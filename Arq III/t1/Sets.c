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
		return;
	}
	int value = getVal(S, 0);

	List minusValue = copy(S);
	List withoutValue = copy(Z);
	List withValue = copy(Z);

	del(&minusValue, value);
	withValue.head = addToList(&withValue, value, true);

	subSets(&minusValue, &withoutValue);
	subSets(&minusValue, &withValue);
}

int main(int argc, const char *argv[])
{
	srand(time(NULL));

	List list;
	list.head = NULL;
	list.current = NULL;
	list.size = 0;

	int i = 0;
	while (i < 15)
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

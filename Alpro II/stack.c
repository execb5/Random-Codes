#include <stdio.h>
#include <stdlib.h>

#define MAX 20

typedef struct {
    int v[MAX];
    int p;
} Stack;


void init_stack(Stack *s) {
    s->p = 0;

    if(s->p == 0)
        fprintf(stderr, "\nStack Inizialized\n\n");
}

int push(Stack *s, int val) {
    if(s->p < MAX) {
        s->v[s->p] = val;
        s->p++;
        return 0;
    }
    else {
        fprintf(stderr, "\nOut of memory: full stack used\n\n");
        show_stack(s);
        exit(1);
    }
    return 0;
}

int pop(Stack *s) {
    if(s->p == 0) {
        fprintf(stderr, "\nStack is empty\n\n");
        exit(1);
    }
    return s->v[--s->p];
}

void show_stack(Stack *s) {
    int i = s->p;
    for(; i >= 0; i--) {
        printf("%d\n", pop(s));
    }
}


int main(int argc, char **argv)
{
    Stack s;
    int i = 1;
    
    init_stack(&s);
    
    for(; i < argc; i++) {
        push(&s, atoi(argv[i]));
    }

    show_stack(&s);

    return 0;
}

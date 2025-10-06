#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

void resize(stack* p,int new_size){
    int* tmp=p->array;
    p->array=malloc(new_size*sizeof(int));
    p->size=new_size;
    p->top=(p->top < p->size-1 ? p->top : p->size-1);
    for(int i=0;i<p->top+1;i++){
        p->array[i]=tmp[i];
    }
    free(tmp);
}


stack* initialize_stack(){
    stack* p=malloc(sizeof(stack));
    p->array=malloc(sizeof(int));
    p->size=1;
    p->top=-1;
    return p;
}


void push(stack* p,int e){
    if(p->top==p->size-1){
        resize(p,p->size*2);
    }
    p->top ++;
    p->array[p->top]=e;
}

int is_empty(stack* p){
    return p->top==-1;
}

int pop(stack* p){
    if(is_empty(p)){
        printf("tentive de dépilement d'une pile vide\n");
        return -1;
    }
    if(p->top<p->size*1/3){
        resize(p,p->size/2);
    }
    int e=p->array[p->top];
    p->top--;
    return e;
}

/*
sommet à gauche, base à droite
 */
void printp(stack* p){
	printf("("); // le '(' indique le début de la pile
	for(int i = p->size - 1; i > p->top; i--){
		if(i == 0){
			printf("-"); //les '_' indiquent des emplacements vides
		}else{
			printf("-/");
		}			
	}
	for(int i = p->top; i >= 0; i--){
		if(i == p->top){
			printf("%d", p->array[i]);
		}else{
			printf("/%d", p->array[i]);
		}		
	}
	printf(")\n"); // la ')' indique la fin de la pile
}

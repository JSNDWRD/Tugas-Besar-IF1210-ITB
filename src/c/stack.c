#include "stack.h"
#include "boolean.h"
#include <string.h>
#include <stdio.h>

#define MAX_OBAT_LENGTH 50
#define MAX_STACK_SIZE 100

void CreateEmptyStack(Stack *S){
    S->top=-1;
}
boolean isStackEmpty(Stack S){
    return S.top==-1;
}
boolean isStackFull(Stack S){
    return S.top==MAX_STACK_SIZE-1;
}

void printStackObat(Stack S){
    for(int i=0; i<S.top; i++){
        printf("%s", S.obat[i]);
        if(i<S.top-1){
            printf(" -> ");
        }
        printf("\n");
    }
}

boolean isStackEqual(Stack S1, Stack S2){
    if(S1.top!=S2.top){
        return false;
    }
    for(int i=0; i<S1.top; i++){
        if(strcmp(S1.obat[i],S2.obat[i])!=0){
            return false;
        }
    }
    return true;
}

void push(Stack *S, Obat val){
    if(!isFull(*S)){
        S->top++;
        strncpy(S->obat[S->top], val, MAX_OBAT_LENGTH);
    }
}
void pop(Stack *S, Obat *val){
    if(!isEmpty(*S)){
        strncpy(*val, S->obat[S->top], MAX_OBAT_LENGTH);
        S->top--;
    }
}
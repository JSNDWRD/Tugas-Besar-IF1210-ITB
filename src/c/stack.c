#include "stack.h"
#include "boolean.h"
#include <string.h>
#include <stdio.h>

#define MAX_OBAT_LENGTH 50
#define MAX_STACK_SIZE 100

void CreateEmpty(Stack *S){
    S->top=-1;
}
boolean isEmpty(Stack S){
    return S.top==-1;
}
boolean isFull(Stack S){
    return S.top==MAX_STACK_SIZE-1;
}
void push(Stack *S, Obat x){
    if(!isFull(*S)){
        S->top++;
        strncpy(S->obat[S->top], x, MAX_OBAT_LENGTH);
    }
}
void pop(Stack *S, Obat x){
    if(!isEmpty(*S)){
        strncpy(x, S->obat[S->top], MAX_OBAT_LENGTH);
        S->top--;
    }
}
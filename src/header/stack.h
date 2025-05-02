#ifndef STACK_H
#define STACK_H

#include "boolean.h"

#define MAX_OBAT_LENGTH 50
#define MAX_STACK_SIZE 100

typedef char Obat[MAX_OBAT_LENGTH];

typedef struct { 
    Obat obat[MAX_STACK_SIZE]; 
    int top;
} Stack;

void CreateEmpty(Stack *S);
boolean isEmpty(Stack S);
boolean isFull(Stack S);
void push(Stack *S, Obat x);
void pop(Stack *S, Obat x);

#endif
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

void CreateEmptyStack(Stack *S);
boolean isStackEmpty(Stack S);
boolean isStackFull(Stack S);
void printStackObat(Stack S);
void push(Stack *S, Obat val);
void pop(Stack *S, Obat *val);

#endif
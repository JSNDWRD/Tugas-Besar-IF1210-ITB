#ifndef STACK_H
#define STACK_H

#include "kamus.h"
#include <string.h>
#include <stdio.h>

void CreateEmptyStack(Stack *S);
boolean isStackEmpty(Stack S);
boolean isStackFull(Stack S);
void printStackObat(Stack S);
boolean isStackEqual(Stack S1, Stack S2);
void push(Stack *S, Obat val);
void pop(Stack *S, Obat *val);

#endif
#ifndef STACK_H
#define STACK_H

#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#define MAX_OBAT_LENGTH 50
#define MAX_STACK_SIZE 100

typedef char Obat[MAX_OBAT_LENGTH];

typedef struct { 
    Obat obat[MAX_STACK_SIZE]; 
    int top;
} Stack;

/* Membuat stack kosong */
void CreateEmptyStack(Stack *s);

/* Mengembalikan true jika stack kosong */
bool IsStackEmpty(Stack s);

/* Mengembalikan true jika stack penuh */
bool IsStackFull(Stack s);

/* Print stack obat (yang berada di perut) */
void PrintStackObat(Stack s);

/* Menambahkan val sebagai elemen top */
void Push(Stack *s, Obat val);

/* Mengambil nilai elemen top, sehingga top yang baru adalah elemen yang datang sebelum elemen top */
void Pop(Stack *s, Obat *val);

#endif
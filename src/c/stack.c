#include "../header/stack.h"
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

/* Konstruktor untuk membuat stack kosong */
void CreateEmptyStack(Stack *s){
    s->top=IDX_UNDEF;
}

/* Mengembalikan true jika stack kosong */
bool IsStackEmpty(Stack s){
    return s.top==IDX_UNDEF;
}

/* Mengembalikan true jika stack penuh */
bool IsStackFull(Stack s){
    return s.top==MAX_STACK_SIZE-1;
}

/* Print stack obat (yang berada di perut) */
void PrintStackObat(Stack s){
    for(int i=0; i<=s.top; i++){
        printf("%s", s.obat[i]);
        if(i<s.top){
            printf(" -> ");
        }
    }
    printf("\n");
}

/* Menambahkan val sebagai elemen top */
void Push(Stack *s, Obat val){
    if(!isStackFull(*s)){
        s->top++;
        strncpy(s->obat[s->top], val, MAX_OBAT_LENGTH);
    }
}

/* Mengambil nilai elemen top, sehingga top yang baru adalah elemen yang datang sebelum elemen top */
void Pop(Stack *s, Obat *val){
    if(!isStackEmpty(*s)){
        strncpy(*val, s->obat[s->top], MAX_OBAT_LENGTH);
        s->top--;
    }
}
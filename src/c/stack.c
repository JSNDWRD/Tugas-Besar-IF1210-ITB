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
    if (IsStackEmpty(s)) {
        printf("Perut kosong.\n");
    } else {
        printf("Isi perut (urutan makan):\n");
        for (int i = s.top; i >= 0; i--) {
            printf("- %s (ID: %d)\n", s.obat[i].nama, s.obat[i].id);
        }
    }
}

/* Menambahkan val sebagai elemen top */
void Push(Stack *s, Obat val){
     if (!IsStackFull(*s)) {
        s->top++;
        s->obat[s->top].id = val.id;
        strncpy(s->obat[s->top].nama, val.nama, MAX_OBAT_LENGTH - 1);
        s->obat[s->top].nama[MAX_OBAT_LENGTH - 1] = '\0'; // pastikan null-terminated
    }
}

/* Mengambil nilai elemen top, sehingga top yang baru adalah elemen yang datang sebelum elemen top */
void Pop(Stack *s, Obat *val){
    if (!IsStackEmpty(*s)) {
        val->id = s->obat[s->top].id;
        strncpy(val->nama, s->obat[s->top].nama, MAX_OBAT_LENGTH - 1);
        val->nama[MAX_OBAT_LENGTH - 1] = '\0'; // pastikan null-terminated
        s->top--;
    }
}
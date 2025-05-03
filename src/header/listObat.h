#ifndef LIST_OBAT_H
#define LIST_OBAT_H

#include "boolean.h"

#define IDX_MIN 0
#define IDX_UNDEF -1
#define MAX_OBAT 100
#define MAX_OBAT_LENGTH 50

//BELUM FIX
typedef char Obat[MAX_OBAT_LENGTH];

typedef struct{
    Obat *buffer;
    int nEff;       
    int capacity;   
} ListObat;

void CreateListDin(ListObat *l, int capacity);

void dealocateList(ListObat *l);
   
boolean isIdxValid(ListObat l, int i);

boolean isIdxEff(ListObat l, int i);

boolean isListEmpty(ListObat l);
   
boolean isListFull(ListObat l);

void readList(ListObat *l){}

void printList(ListObat l);

int indexOf(ListObat l, Obat val);

void insertLast(ListObat *l, Obat val);

void deleteLast(ListObat *l, Obat *val);

void deleteAt(ListObat *l, Obat *val, int idx);

void expandList(ListObat *l, int num);

void shrinkList(ListObat *l, int num);

void compressList(ListObat *l);
   
#endif
#ifndef LIST_OBAT_H
#define LIST_OBAT_H

#include "kamus.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

//MASIH BISA BERUBAH

void CreateListDin(ListObat *l, int capacity);

void dealocateList(ListObat *l);
   
boolean isIdxValid(ListObat l, int i);

boolean isIdxEff(ListObat l, int i);

boolean isListEmpty(ListObat l);
   
boolean isListFull(ListObat l);

void readList(ListObat *l);

void printList(ListObat l);

int indexOf(ListObat l, Obat val);

void insertLast(ListObat *l, Obat val);

void insertAt(ListObat *l, Obat val, int idx);

void deleteLast(ListObat *l, Obat *val);

void deleteAt(ListObat *l, Obat *val, int idx);

void expandList(ListObat *l, int num);

void shrinkList(ListObat *l, int num);

void compressList(ListObat *l);
   
#endif
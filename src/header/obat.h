#ifndef OBAT_H
#define OBAT_H

#include "stack.h"
#include "listObat.h"
#include "kamus.h"
#include <string.h>
#include <stdio.h>

void MinumObat(ListObat *l, Stack *perut);
void MinumPenawar(ListObat *l, Stack *perut);
void PulangDok(ListObat l, Stack urutan, Stack perut);

#endif
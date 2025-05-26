#ifndef OBAT_H
#define OBAT_H

#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "stack.h"
#include "ngobatin.h"
#include "user.h"

//
void MinumObat(User *user);

//
void MinumPenawar(User *user);

//
bool IsUrut(ObatList urutanObat, Stack perut);

//
void PulangDok(Session *session, ObatList urutanObat, ObatList obatList);

#endif
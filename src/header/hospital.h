#ifndef HOSPITAL_H
#define HOSPITAL_H

#include <stdio.h>
#include "matrix.h"
#include "user.h"

void LoadConfig(Matrix *denahHospital, char *inputFolder);
/* Membaca file eksternal dan memasukkan data config ke dalam denahHospital */

void UbahInput(const char *input, int *row, int *col);
/*Menentukan baris dan kolom yang sesuai dengan input ruangan */

void SaveConfig(Matrix denahHospital);
/* Menyimpan matrix denahHospital ke dalam file eksternal config.txt */

#endif
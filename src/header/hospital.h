#ifndef HOSPITAL_H
#define HOSPITAL_H

#include <stdio.h>
#include "matrix.h"
#include "user.h"

/* Membaca file eksternal dan memasukkan data config ke dalam denahHospital */
void LoadConfig(Matrix *denahHospital, char *inputFolder);

/*Menentukan baris dan kolom yang sesuai dengan input ruangan */
void UbahInput(const char *input, int *row, int *col);

/* Menyimpan matrix denahHospital ke dalam file eksternal config.txt */
void SaveConfig(Matrix denahHospital);


#endif
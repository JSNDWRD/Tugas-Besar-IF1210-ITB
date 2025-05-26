#ifndef HOSPITAL_H
#define HOSPITAL_H

#include <stdio.h>
#include "matrix.h"
#include "ngobatin.h"
#include "dokter.h"
#include "user.h"
#include "stack.h"

/* Membaca file eksternal dan memasukkan data config ke dalam denahHospital */
void LoadConfig(Matrix *denahHospital, char *inputFolder, UserList *userlist);

/*Menentukan baris dan kolom yang sesuai dengan input ruangan */
void UbahInput(char *input, int *row, int *col);

/*Untuk lihat denah*/
void LihatDenah(Matrix *denahHospital);

/*Untuk lihat ruangan yang sesuai*/
void LihatRuangan(Matrix *denahHospital, char *input, UserList *userlist);

/* Menyimpan matrix denahHospital ke dalam file eksternal config.txt */
void SaveConfig(Matrix *denahHospital, char* inputFolder, UserList *userlist);


#endif
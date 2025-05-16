#ifndef HOSPITAL_H
#define HOSPITAL_H

#include <stdio.h>
#include "matrix.h"
#include "ngobatin.h"
#include "user.h"

/* Membaca file eksternal dan memasukkan data config ke dalam denahHospital */
void LoadConfig(Matrix *denahHospital, char *inputFolder, UserList *userlist);

void UbahInput(char *input, int *row, int *col);
/*Menentukan baris dan kolom yang sesuai dengan input ruangan */

void LihatDenah(Matrix *denahHospital);
/*Untuk lihat denah*/

void LihatRuangan(Matrix *denahHospital, char *input, UserList userlist);
/*Untuk lihat ruangan yang sesuai*/

/* Menyimpan matrix denahHospital ke dalam file eksternal config.txt */
void SaveConfig(Matrix *denahHospital, char* inputFolder, UserList *userlist);


#endif
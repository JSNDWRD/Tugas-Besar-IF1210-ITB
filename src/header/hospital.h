#ifndef HOSPITAL_H
#define HOSPITAL_H

#include <stdio.h>
#include "matrix.h"

void LoadConfig(Matrix *denahHospital);
/* Membaca file eksternal dan memasukkan data config ke dalam denahHospital */

void saveConfig(Matrix denahHospital);
/* Menyimpan matrix denahHospital ke dalam file eksternal config.txt */

#endif
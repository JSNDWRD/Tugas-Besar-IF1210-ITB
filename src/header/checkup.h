#ifndef CHECKUP_H
#define CHECKUP_H

#include "./utils.h"
#include "./user.h"
#include "./hospital.h"

// Fungsi validasi input data medis
void InputDataMedis(float *suhu, int *sistolik, int *diastolik, int *detak, float *saturasi, int *gula, float *berat, int *tinggi, int *kolesterol, int *trombosit);

// Fungsi untuk memasukkan data medis pasien serta masuk ke queue dokter
void DaftarCheckup(UserList *userList, Session *session, Matrix *denahRumahSakit);

// Pasien yang sudah melakukan pendaftaran dapat melihat status antriannya
void LihatAntrianSaya(UserList *userList, Session *session, Matrix *denahRumahSakit);

#endif
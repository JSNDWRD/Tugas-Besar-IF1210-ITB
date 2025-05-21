#ifndef CHECKUP_H
#define CHECKUP_H

// Fungsi validasi input data medis
void InputDataMedis(float *suhu, int *sistolik, int *diastolik, int *detak, float *saturasi, int *gula, float *berat, int *tinggi, int *kolesterol, int *ldl, int *trombosit);

// Fungsi untuk memasukkan data medis pasien serta masuk ke queue dokter
void DaftarCheckup(UserList *userList, Session *session, Matrix *denahRumahSakit);

# endif
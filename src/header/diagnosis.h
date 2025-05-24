#ifndef DIAGNOSIS_H
#define DIAGNOSIS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hospital.h"

#define PENYAKIT_CAPACITY 500

/* Definisi ADT Sederhana Penyakit */
typedef struct
{
    int id;
    char namaPenyakit[100];
    float suhuTubuhMin;
    float suhuTubuhMax;
    int tekananDarahSistolikMin;
    int tekananDarahSistolikMax;
    int tekananDarahDiastolikMin;
    int tekananDarahDiastolikMax;
    int detakJantungMin;
    int detakJantungMax;
    float saturasiOksigenMin;
    float saturasiOksigenMax;
    int kadarGulaDarahMin;
    int kadarGulaDarahMax;
    float beratBadanMin;
    float beratBadanMax;
    int tinggiBadanMin;
    int tinggiBadanMax;
    int kadarKolesterolMin;
    int kadarKolesterolMax;
    int trombositMin;
    int trombositMax;
} Penyakit;

// ADT List Penyakit
typedef struct
{
    Penyakit penyakit[PENYAKIT_CAPACITY];
    int nEff;
} PenyakitList;

/* Membaca file eksternal penyakit.csv dan menuliskannya ke dalam List penyakitList */
void LoadPenyakit(PenyakitList *penyakitList, char *inputFolder);

/* Mendiagnosis apakah user terjangkit suatu penyakit atau tidak */
void Diagnosis(User user, PenyakitList penyakitList, char *namaPenyakit);

/* Mengembalikan ID Penyakit berdasarkan nama penyakit */
int GetPenyakitID(PenyakitList penyakitList, char *namaPenyakit);

/* Mengembalikan index ruangan yang berisi pasien yang ditangani dokter yang sedang login */
void SearchRuangan(int doctorId, Matrix *denahHospital, int *indeksRuangan);

/* Memajukan antrian setelah pasien telah didiagnosis */
void ShiftAntrianRuangan(Matrix *denahHospital, Ruangan *currentRuangan);

void SavePenyakit(char *folderAsal, char *folderTujuan);

#endif
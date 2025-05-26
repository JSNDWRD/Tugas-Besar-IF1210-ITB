#ifndef NGOBATIN_H
#define NGOBATIN_H

#include <stdio.h>
#include <string.h>
#include "./utils.h"
#include "./types.h"

#define OBAT_CAPACITY 500
#define VAL_UNDEF "-"
#define STR_LENGTH 500

/* Definisi ADT Map Obat-Penyakit beserta ADT List Obat */

// Elemen Map berdasarkan penyakitId
typedef struct
{
    int penyakitId;
    int obatId[100];
    int urutan;
} ObatEntry;

// Map
typedef struct
{
    ObatEntry buffer[500];
    int length;
    int banyakObat;
} ObatMap;

// List
typedef struct
{
    Obat obats[OBAT_CAPACITY];
    int length;
} ObatList;

void CreateObatMap(ObatMap *obatMap);

void CreateObatList(ObatMap *obatMap);

// Mereturn panjang dari obatMap
int ObatMapLength(ObatMap obatMap);

// Mereturn panjang dari obatList
int ObatListLength(ObatList obatList);

// Mereturn Entry obat pada indeks ke-i
ObatEntry GetObatEntry(ObatMap obatMap, int i);

// Mereturn obat pada indeks ke-i dalam list obat
Obat GetObat(ObatList obatList, int i);

// Mereturn obat sesuai dengan id yang diberikan
Obat GetObatById(ObatList obatList, int idx);

// Mereturn obat seusai dengan nama yang diberikan
Obat GetObatByName(ObatList obatList, const char *namaPenyakit);

// Mencari indeks dari obat berdasarkan nama penyakit
int SearchObatIndex(ObatMap obatMap, const char *penyakit);

// Mencetak obat-obatan yang harus dikonsumsi berdasarkan penyakit
void PrintObat(ObatMap obatMap, int penyakitId, ObatList obatList, const char *namaPenyakit, char arrayUrutanObat[][500], User *pasien);

void LoadObat(ObatList *obatList, char *inputFolder);

void LoadObatMap(ObatMap *obatMap, char *inputFolder);

void SaveObat(char *folderAsal, char *folderTujuan);

void MinumObat(ObatList obatList, User *user, char arrayNamaObat[][500]);

#endif
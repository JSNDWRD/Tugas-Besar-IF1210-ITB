#ifndef NGOBATIN_H
#define NGOBATIN_H

#include <stdio.h>
#include <string.h>
#include "./utils.h"

#define OBAT_CAPACITY 500
#define VAL_UNDEF "-"
#define STR_LENGTH 100

/* Definisi ADT Map Obat-Penyakit beserta ADT List Obat */

// Elemen Map berdasarkan penyakitId
typedef struct {
    int penyakitId;
    int obatId[100];
    int urutan;
} ObatEntry;

// Map
typedef struct {
    ObatEntry buffer[500];
    int length;
} ObatMap;

// Elemen List
typedef struct {
    int id;
    char nama[STR_LENGTH];
} Obat;

// List
typedef struct {
    Obat obats[OBAT_CAPACITY];
    int length;
} ObatList;


/* KONSTRUKTOR */
void CreateObatMap(ObatMap *obatMap);
void CreateObatList(ObatMap *obatMap);

/* SELEKTOR */

// Mereturn panjang dari obatMap
int ObatMapLength(ObatMap obatMap);

// Mereturn panjang dari obatList
int ObatListLength(ObatList obatList);

// Mereturn Entry obat pada indeks ke-i
ObatEntry GetObatEntry(ObatMap obatMap, int i);

// Mereturn obat pada indeks ke-i dalam list obat
Obat GetObat(ObatList obatList, int i);

// Mencari indeks dari obat berdasarkan nama penyakit
int SearchObatIndex(ObatMap obatMap, const char *penyakit);

// Mencetak obat-obatan yang harus dikonsumsi berdasarkan penyakit
void PrintObat(ObatMap obatMap, const char *penyakit);


/* OPERASI FILE EKSTERNAL */
void LoadObat(ObatList *obatList, char* inputFolder);
void LoadObatMap(ObatMap *obatMap, char* inputFolder);

#endif
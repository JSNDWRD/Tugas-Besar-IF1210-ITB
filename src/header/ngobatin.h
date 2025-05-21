#ifndef NGOBATIN_H
#define NGOBATIN_H

#define OBAT_CAPACITY 500
#define VAL_UNDEF "-"
#define STR_LENGTH 100

/* Definisi ADT Map Obat */

// Elemen Map
typedef struct {
    char penyakit[STR_LENGTH];
    char obat[STR_LENGTH];
} ObatEntry;

// Map
typedef struct {
    ObatEntry buffer[500];
    int length;
} ObatMap;


/* KONSTRUKTOR */

/* SELEKTOR */

#endif
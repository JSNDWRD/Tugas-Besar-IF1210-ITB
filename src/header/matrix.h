#ifndef MATRIX_H
#define MATRIX_H

#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ROWS 100
#define MAX_COLS 100

typedef struct {
  int pasien[100];  // menyimpan semua id pasien yang ada didalam ruangan
  int jumlahPasien; 
  int dokter;  // menyimpan id dokter yang ada di ruangan
  int kapasitas;  // kapasitas ruangan
  char namaRuangan[10];  //menyimpan nama ruangan (contoh : A1, B2, dll)
} Ruangan;


typedef struct {
  Ruangan data[MAX_ROWS][MAX_COLS];
  int rows;
  int cols;
} Matrix;

/* Konstruktor */

// Membuat matrix baru dengan ukuran rows x cols
void CreateMatrix(int rows, int cols, Matrix *M);
/* I.S. rows dan cols terdefinisi dan valid (1 <= rows,cols <= MAX) */
/* F.S. Terbentuk matrix M dengan ukuran rows x cols */

/*Mengembalikan true jika baris valid pada Matrix M, dan sebaliknya*/
bool isRowValid(int rows,Matrix M);

/*Mengembalikan true jika kolom valid pada Matrix M, dan sebaliknya*/
bool isColsValid(int cols,Matrix M);

/* Selector */

/* Mengembalikan jumlah baris matrix M */
int GetRows(Matrix M);

/* Mengembalikan jumlah kolom matrix M */
int GetCols(Matrix M);

// Mengembalikan nilai elemen pada baris row dan kolom col
Ruangan *GetElement(Matrix *M, int row, int col);
/* Mengembalikan pointer ke elemen matrix M pada baris row dan kolom col */
/* Mengembalikan NULL jika row atau col tidak valid untuk matrix M */

/* Mutator */

// Mengubah nilai elemen pada baris row dan kolom col, return true jika berhasil
bool SetElement(Matrix *M, int row, int col, Ruangan value);
/* I.S. M terdefinisi */
/* F.S. Jika row dan col valid, elemen M pada baris row dan kolom col bernilai value, mengembalikan true */
/*      Jika row atau col tidak valid, mengembalikan false */

// Inisialisasi semua elemen matrix M dengan <Huruf><Angka>
void InisialisasiNamaRuangan(Matrix *M);

#endif
/* File : matrix.h */
/* Deskripsi : Definisi ADT Matrix untuk representasi matriks dengan elemen float */
#ifndef MATRIX_H
#define MATRIX_H
#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#define MAX_ROWS 100
#define MAX_COLS 100

typedef struct 
{
  int pasien[100]; // menyimpan semua id pasien yang ada didalam ruangan
  int jumlahpasien; 
  int dokter; // menyimpan id dokter yang ada di ruangan
  int kapasitas; // kapasitas ruangan
  char namaruangan[10]; //menyimpana nama ruangan (contoh : A1,B2,dll)
}Ruangan;


typedef struct
{
  Ruangan data[MAX_ROWS][MAX_COLS];
  int rows;
  int cols;
} Matrix;

/* Konstruktor */
void CreateMatrix(int rows, int cols, Matrix *M);
/* I.S. rows dan cols terdefinisi dan valid (1 <= rows,cols <= MAX) */
/* F.S. Terbentuk matrix M dengan ukuran rows x cols */

bool isRowValid(int rows,Matrix M);
/*Mengembalukan true jika baris valid pada Matrix M, dan sebaliknya*/

bool isColsValid(int cols,Matrix M);
/*Mengembalikan true jika colom validpada Matrix M, dan sebaliknya*/


/* Selector */
int GetRows(Matrix M);
/* Mengembalikan jumlah baris matrix M */

int GetCols(Matrix M);
/* Mengembalikan jumlah kolom matrix M */

Ruangan *GetElement(Matrix *M, int row, int col);
/* Mengembalikan pointer ke elemen matrix M pada baris row dan kolom col */
/* Mengembalikan NULL jika row atau col tidak valid untuk matrix M */

/* Mutator */
bool SetElement(Matrix *M, int row, int col, Ruangan value);
/* I.S. M terdefinisi */
/* F.S. Jika row dan col valid, elemen M pada baris row dan kolom col bernilai value, mengembalikan true */
/*      Jika row atau col tidak valid, mengembalikan false */


void InisialisasiNamaRuangan(Matrix *M);
/*Menginisialisasi nama ruangan berdasarkan baris dan kolom yang dipunyai*/

#endif
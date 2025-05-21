#ifndef MATRIX_H
#define MATRIX_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dokter.h"

#define MAX_ROWS 100
#define MAX_COLS 100

typedef struct {
  // int pasien[100];  // menyimpan semua id pasien yang ada didalam ruangan
  int jumlahPasien; 
  int dokter;  // menyimpan id dokter yang ada di ruangan
  int kapasitas;  // kapasitas ruangan
  char namaRuangan[12];  //menyimpan nama ruangan (contoh : A1,B2,dll)
  Queue antrianPasien;
} Ruangan;


typedef struct {
  Ruangan data[MAX_ROWS][MAX_COLS];
  int rows;
  int cols;
} Matrix;


// Membuat matrix baru dengan ukuran rows x cols
void CreateMatrix(int rows, int cols, Matrix *M);

/*Mengembalikan true jika baris valid pada Matrix M, dan sebaliknya*/
bool isRowValid(int rows,Matrix M);

/*Mengembalikan true jika kolom valid pada Matrix M, dan sebaliknya*/
bool isColsValid(int cols,Matrix M);

// Mengembalikan letak ruangan dimana dokter berada
void FindDokter(Matrix *M, int *row, int *col, char *namaRuangan, int dokterId);

/* Mengembalikan jumlah baris matrix M */
int GetRows(Matrix M);

/* Mengembalikan jumlah kolom matrix M */
int GetCols(Matrix M);

// Mengembalikan nilai elemen pada baris row dan kolom col
Ruangan *GetRuangan(Matrix *M, int row, int col);

// Mengubah nilai elemen pada baris row dan kolom col, return true jika berhasil
bool SetElement(Matrix *M, int row, int col, Ruangan value);

// Inisialisasi semua elemen matrix M dengan <Huruf><Angka>
void InisialisasiNamaRuangan(Matrix *M);

#endif
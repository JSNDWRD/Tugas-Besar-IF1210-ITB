// #include <stdio.h>
// #include "../header/matrix.h"
// /* Konstruktor */
// void CreateMatrix(int rows, int cols, Matrix *M){
//     M->rows = rows;
//     M->cols = cols;
//     for(int i = 0; i < rows; i++) {
//         for(int j = 0; j < cols; j++) {
//             M->data[i][j].jumlahPasien = 0;
//             M->data[i][j].dokter = -1;
//             M->data[i][j].kapasitas = 0;
//             for (int k = 0; k < 100; k++) M->data[i][j].pasien[k] = -1;
//         }
//     }
// }

// bool isRowValid(int rows,Matrix M){
//     return (rows >= 0 || rows < M.rows);
// }
  
// bool isColsValid(int cols,Matrix M){
//     return (cols >= 0 || cols < M.cols);
// }

// int GetRows(Matrix M){
//     return M.rows;
// }

// int GetCols(Matrix M){
//     return M.cols;
// }


// Ruangan *GetElement(Matrix *M, int row, int col){
//     if(row >= M->rows || col >= M->cols){
//         return NULL;
//     } else {
//         return &M->data[row][col];
//     }
// }


// bool SetElement(Matrix *M, int row, int col, Ruangan value){
//     if(row >= M->rows || col >= M->cols){
//         return false;
//     } else {
//         M->data[row][col] = value;
//         return true;
//     }
// }

// void InisialisasiNamaRuangan(Matrix *M) {
//     for (int i = 0; i < M->rows; i++) {
//         for (int j = 0; j < M->cols; j++) {
//             // Huruf baris + nomor kolom
//             // Misalnya baris 0 kolom 1 -> A2
//             sprintf(M->data[i][j].namaRuangan, "%c%d", 'A' + i, j + 1);
//         }
//     }
// }


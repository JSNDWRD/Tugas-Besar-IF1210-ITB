#include <stdio.h>
#include "../header/matrix.h"
#include "../header/manager.h"

void CreateMatrix(int rows, int cols, Matrix *M)
{
    M->rows = rows;
    M->cols = cols;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            M->data[i][j].jumlahPasienDalamRuangan = 0;
            M->data[i][j].jumlahPasienDiAntrian = 0;
            M->data[i][j].dokter = -1;
            M->data[i][j].kapasitasRuangan = 0;
            M->data[i][j].kapasitasAntrian = 0;
            createQueue(&M->data[i][j].antrianPasien);
            // for (int k = 0; k < 100; k++) M->data[i][j].pasien[k] = -1;
        }
    }
}

bool isRowValid(int rows, Matrix M)
{
    return (rows >= 0 && rows < M.rows);
}

bool isColsValid(int cols, Matrix M)
{
    return (cols >= 0 && cols < M.cols);
}

int GetRows(Matrix M)
{
    return M.rows;
}

int GetCols(Matrix M)
{
    return M.cols;
}

void FindDokter(Matrix *M, int *row, int *col, char *namaRuangan, int dokterId)
{
    for (int i = 0; i < M->rows; i++)
    {
        for (int j = 0; j < M->cols; j++)
        {
            if (M->data[i][j].dokter == dokterId)
            {
                *row = i;
                *col = j;
                strcpy(namaRuangan, M->data[i][j].namaRuangan);
                return;
            }
        }
    }
    strcpy(namaRuangan, "-");
}

Ruangan *GetRuangan(Matrix *M, int row, int col)
{
    if (row >= M->rows || col >= M->cols)
    {
        return NULL;
    }
    else
    {
        return &M->data[row][col];
    }
}

bool SetElement(Matrix *M, int row, int col, Ruangan value)
{
    if (row >= M->rows || col >= M->cols)
    {
        return false;
    }
    else
    {
        M->data[row][col] = value;
        return true;
    }
}

void InisialisasiNamaRuangan(Matrix *M)
{
    for (int i = 0; i < M->rows; i++)
    {
        for (int j = 0; j < M->cols; j++)
        {
            // Huruf baris + nomor kolom
            // Misalnya baris 0 kolom 1 -> A2
            snprintf(M->data[i][j].namaRuangan, sizeof(M->data[i][j].namaRuangan), "%c%d", 'A' + i, j + 1);
        }
    }
}

void printAntrianRuangan(Ruangan ruangan, UserList *userList)
{
    Node *curr = ruangan.antrianPasien.head;
    for (int i = 0; i < ruangan.jumlahPasienDalamRuangan; i++) {
        if (curr == NULL) {
            break;
        }
        curr = curr->next;
    }
    printf("Pasien di antrian:\n");
    int count = 0;
    while (curr != NULL)
    {
        printf("%d. %s\n", count + 1, GetUserById(userList, curr->data).username);
        curr = curr->next;
        count++;
    }
    if (count == 0)
    {
        printf("Tidak ada pasien pada antrian ruangan.\n");
    }
    printf("\n");
}
#ifndef MANAGER_H
#define MANAGER_H

#include <stdio.h>
#include "auth.h"
#include "user.h"

// Hanya digunakan oleh manager, untuk melihat user, sort berdasarkan id atau nama.
void LihatUser(UserList *userList, Session *session);

// Hanya digunakan oleh manager, untuk melihat pasien, sort berdasarkan id atau nama.
void LihatPasien(UserList *userList, Session *session);

// Hanya digunakan oleh manager, untuk melihat dokter, sort berdasarkan id atau nama.
void LihatDokter(UserList *userList, Session *session);

// Sorting dengan selection sort, berdasarkan id atau nama
void SelectionSort(UserList *userList, int n, int basedOn, int order);

// Function bantuan untuk menampilkan pilihan
void PrintPilihan(int *pil1, int *pil2);

// Print userlist
void PrintList(UserList *userList, int basedOn, int order);

// Cari user dengan binary search
void CariUser(UserList *userList, Session *session);

// Cari pasien dengan binary search
void CariPasien(UserList *userList, Session *session);

// Cari dokter dengan binary search
void CariDokter(UserList *userList, Session *session);

// searching user dengan binary search
int BinarySearchUser(UserList *userList, const char *username, int *index);


#endif
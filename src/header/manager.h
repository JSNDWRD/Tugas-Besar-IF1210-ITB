#ifndef MANAGER_H
#define MANAGER_H

#include <stdio.h>
#include "auth.h"
#include "user.h"
#include "utils.h"
#include "matrix.h"
#include "hospital.h"

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

// searching user dengan binary search -> untuk search ID
int BinarySearchUser(UserList *userList, int id, int *index);

// searching user dengan sequence search -> untuk search username
int SequenceSearchUser(UserList *userList, char *username, int *index);

// Get user from UserList by index
User GetUserAt(UserList *userList, int idx);

// Get user from UserList by its id
User GetUserById(UserList *userList, int userId);

// Set user in UserList by index
void SetUserAt(UserList *userList, int idx, User user);

// Add user to UserList (if not full)
int AppendUser(UserList *userList, User user);

// Assign dokter ke ruangan tertentu
void AssignDokter(UserList *userList, Matrix *denahRumahSakit);

#endif
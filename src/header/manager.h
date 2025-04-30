#ifndef MANAGER_H
#define MANAGER_H

#include <stdio.h>
#include "auth.h"
#include "user.h"

// Hanya digunakan oleh manager, untuk melihat user, sort berdasarkan id atau nama.
void LihatUser(UserList *userList, Session *session);

// Sorting dengan selection sort, berdasarkan id atau nama
void SelectionSort(UserList *userList, int n, int basedOn, int order) ;

// Function bantuan untuk menampilkan pilihan
void PrintPilihan(int *pil1, int *pil2);

// Print userlist
void PrintList(UserList *userList, int basedOn, int order);
#endif
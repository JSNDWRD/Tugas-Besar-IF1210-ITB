#ifndef AUTH_H
#define AUTH_H

#include <stdio.h>
#include <string.h>
#include "user.h"
#include "utils.h"

// Untuk login, register, dan logout
// Nanti bagian login, etc. di user.h dihapus

#define MAX_USERS 100
#define MAX_SET_SIZE 200

#define MAX_UNIQUE_CODE 50

// Implementasi Set
typedef struct {
    char username[MAX_SET_SIZE][MAX_USERNAME_LENGTH];
    int count;  // Jumlah elemen dalam set
} Set;

// Membuat set baru, count = 0;
Set CreateNewSet();

// Insert elemen ke Set
void InsertSet(Set *set, char *value);

// Cek apakah value sudah ada di Set
int IsInSet(Set *set, char *value);  

// Login user
void Login(UserList *userList, Session *session);

// Daftar user, khusus pasien
void RegisterUser(UserList *userList, Session *session);

// Menambahkan user, digunakan manager
void TambahDokter(UserList *userList, Session *session);

// Logout user
void Logout(Session *session);

void ResetPassword(UserList *userList, Session *session);


#endif

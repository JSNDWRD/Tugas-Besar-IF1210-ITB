#ifndef _USER_H_
#define _USER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Manajemen User
// Header untuk fungsi yang berhubungan dengan file eksternal

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

/* Definisi Type User */
typedef struct {
    int id;
    char username[MAX_USERNAME_LENGTH];  // Keunikan dicek secara case-insensitive
    char password[MAX_PASSWORD_LENGTH];
    char role[10];  // "manager" / "dokter" / "pasien"
    char riwayatPenyakit[50];  // Nama penyakit (bisa "-" jika kosong)
    
    // Data di bawah bernilai -1 jika tidak terdapat data tersebut dalam file CSV
    float suhuTubuh;
    int tekananDarahSistolik;
    int tekananDarahDiastolik;
    int detakJantung;
    float saturasiOksigen;
    float kadarGulaDarah;
    float beratBadan;
    int tinggiBadan;
    int kadarKolesterol;
    int kadarKolesterolLDL;
    int trombosit;
} User;

/* Definisi Type UserList */
typedef struct {
    User users[100];
    int count;
} UserList;

/* Definisi Type Session */
typedef struct {
    int loggedIn;  // 1 jika user sudah login, 0 jika tidak
    User currentUser;  // Data user pada sesi sekarang
} Session;

User CreateNewUser(int id, char *username, char *password, char *role, char *riwayatPenyakit,
                float suhuTubuh, int tekananDarahSistolik, int tekananDarahDiastolik, int detakJantung,
                float saturasiOksigen, float kadarGulaDarah, float beratBadan, int tinggiBadan,
                int kadarKolesterol, int kadarKolesterolLDL, int trombosit);

/* Membaca file eksternal dan memasukkan data user yang terdaftar ke dalam userList  */
void LoadUsers(UserList *userList);
/* Membaca file eksternal dan memasukkan data user yang terdaftar ke dalam userList  */
void LoadUsers(UserList *userList);

/* Logout user dengan memvalidasi apakah sudah logged in atau belum */
void Logout(Session *session);

// Tambah user ke list
void AddUser(UserList *userList, User newUser);


#endif

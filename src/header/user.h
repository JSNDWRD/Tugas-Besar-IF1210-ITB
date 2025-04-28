#ifndef _USER_H_
#define _USER_H_

#include <stdio.h>

// Manajemen User
// Header untuk feature login, register, logout

/* Definisi Type User */
typedef struct {
    int id;
    char username[50]; // Keunikan dicek secara case-insensitive
    char password[50];
    char role[10]; // "manager" / "dokter" / "pasien"
    char riwayatPenyakit[50]; // Nama penyakit (bisa "-" jika kosong)
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
    int loggedIn; // 1 jika user sudah login, 0 jika tidak
    User currentUser; // Data user pada sesi sekarang
} Session;

/* Membaca file eksternal dan memasukkan data user yang terdaftar ke dalam userList  */
void LoadUsers(UserList *userList);

/* Login user sesuai username dan password yang diinput */
void Login(UserList *userList, Session *session);

/* Daftar user sesuai username dan password yang diinput */
void RegisterUser(UserList *userList);

/* Logout user dengan memvalidasi apakah sudah logged in atau belum */
void Logout(Session *session);


#endif

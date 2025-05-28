#ifndef _USER_H_
#define _USER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"

// Manajemen User
// Header untuk fungsi yang berhubungan dengan file eksternal

#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

/* Definisi ADT User */
typedef struct
{
    int id;
    char username[MAX_USERNAME_LENGTH]; // Keunikan dicek secara case-insensitive
    char password[MAX_PASSWORD_LENGTH];
    char role[10];            // "manager" / "dokter" / "pasien"
    char riwayatPenyakit[50]; // Nama penyakit (bisa "-" jika kosong)
    int diagnosa;
    int ngobatin;
    int obat[100];         // inventory obat yang dipunyai pasien
    int urutanNgobat[100]; // urutan id obat yang harus dimakan pasien
    int jumlahNgobat;
    int jumlahObat;
    Stack perut; // obat yang sudah di makan
    int jumlahObatMasukPerut;

    // Data di bawah bernilai -1 jika tidak terdapat data tersebut dalam file CSV
    float suhuTubuh;
    int tekananDarahSistolik;
    int tekananDarahDiastolik;
    int detakJantung;
    float saturasiOksigen;
    int kadarGulaDarah;
    float beratBadan;
    int tinggiBadan;
    int kadarKolesterol;
    int trombosit;
} User;

/* Definisi Type UserList */
typedef struct
{
    User users[100];
    int count;
    int pasienDenganObat;
    int pasienKondisiPerut;
} UserList;

/* Definisi Type Session */
typedef struct
{
    int loggedIn;     // 1 jika user sudah login, 0 jika tidak
    User currentUser; // Data user pada sesi sekarang
} Session;

/* Membentuk user berdasarkan komponen-komponen yang dimasukkan */
void CreateUser(User *user, int id, char *username, char *password, char *role, char *riwayatPenyakit,
                float suhuTubuh, int tekananDarahSistolik, int tekananDarahDiastolik, int detakJantung,
                float saturasiOksigen, int kadarGulaDarah, float beratBadan, int tinggiBadan,
                int kadarKolesterol, int trombosit);

/* Mendapatkan komponen ID dari user */
int GetID(User *user);

/* Mendapatkan komponen Username dari user */
char *GetUsername(User *user);

/* Mendapatkan komponen Password dari user */
char *GetPassword(User *user);

/* Mendapatkan komponen Role dari user */
char *GetRole(User *user);

/* Mendapatkan komponen RiwayatPenyakit dari user */
char *GetRiwayatPenyakit(User *user);

/* Mendapatkan komponen SuhuTubuh dari user */
float GetSuhuTubuh(User *user);

/* Mendapatkan komponen TekananDarahSistolik dari user */
int GetTekananDarahSistolik(User *user);

/* Mendapatkan komponen TekananDarahDiastolik dari user */
int GetTekananDarahDiastolik(User *user);

/* Mendapatkan komponen DetakJantung dari user */
int GetDetakJantung(User *user);

/* Mendapatkan komponen SaturasiOksigen dari user */
float GetSaturasiOksigen(User *user);

/* Mendapatkan komponen KadarGulaDarah dari user */
float GetKadarGulaDarah(User *user);

/* Mendapatkan komponen BeratBadan dari user */
float GetBeratBadan(User *user);

/* Mendapatkan komponen TinggiBadan dari user */
int GetTinggiBadan(User *user);

/* Mendapatkan komponen KadarKolesterol dari user */
int GetKadarKolesterol(User *user);

/* Mendapatkan komponen KadarKolesterolLDL dari user */
int GetKadarKolesterolLDL(User *user);

/* Mendapatkan komponen Trombosit dari user */
int GetTrombosit(User *user);

/* Mengubah nilai komponen ID dari user menjadi val */
void SetID(User *user, int val);

/* Mengubah nilai komponen Username dari user menjadi val */
void SetUsername(User *user, char *val);

/* Mengubah nilai komponen Password dari user menjadi val */
void SetPassword(User *user, char *val);

/* Mengubah nilai komponen Role dari user menjadi val */
void SetRole(User *user, char *val);

/* Mengubah nilai komponen RiwayatPenyakit dari user menjadi val */
void SetRiwayatPenyakit(User *user, char *val);

/* Mengubah nilai komponen SuhuTubuh dari user menjadi val */
void SetSuhuTubuh(User *user, float val);

/* Mengubah nilai komponen TekananDarahSistolik dari user menjadi val */
void SetTekananDarahSistolik(User *user, int val);

/* Mengubah nilai komponen TekananDarahDiastolik dari user menjadi val */
void SetTekananDarahDiastolik(User *user, int val);

/* Mengubah nilai komponen DetakJantung dari user menjadi val */
void SetDetakJantung(User *user, int val);

/* Mengubah nilai komponen SaturasiOksigen dari user menjadi val */
void SetSaturasiOksigen(User *user, float val);

/* Mengubah nilai komponen KadarGulaDarah dari user menjadi val */
void SetKadarGulaDarah(User *user, int val);

/* Mengubah nilai komponen BeratBadan dari user menjadi val */
void SetBeratBadan(User *user, float val);

/* Mengubah nilai komponen TinggiBadan dari user menjadi val */
void SetTinggiBadan(User *user, int val);

/* Mengubah nilai komponen KadarKolesterol dari user menjadi val */
void SetKadarKolesterol(User *user, int val);

/* Mengubah nilai komponen KadarKolesterolLDL dari user menjadi val */
void SetKadarKolesterolLDL(User *user, int val);

/* Mengubah nilai komponen Trombosit dari user menjadi val */
void SetTrombosit(User *user, int val);

/* Menambahkan user ke dalam array userList */
void AddUser(UserList *userList, User newUser);

/* Membaca file eksternal dan memasukkan data user yang terdaftar ke dalam userList */
void LoadUsers(UserList *userList, char *inputFolder);

/* Menyimpan array userList ke dalam file eksternal user.csv */
void SaveUsers(UserList *userList, char *inputFolder);

#endif
#include "../header/checkup.h"
#include "../header/matrix.h"
#include "../header/dokter.h"
#include "../header/user.h"
#include <stdio.h>
#include <string.h>

void InputDataMedis(float *suhu, int *sistolik, int *diastolik, int *detak, float *saturasi, int *gula, float *berat, int *tinggi, int *kolesterol, int *ldl, int *trombosit) {
    printf("Masukkan data medis:\n");
    do {
        printf("Suhu tubuh (°C): ");
        scanf("%f", suhu);

        if (*suhu < 0) {
            printf("Suhu tidak valid.\n");
        }
    }
    while (*suhu <= 0);

    do {
        printf("Tekanan darah (sistol/distol): ");
        scanf("%d %d", sistolik, diastolik);

        if (*sistolik < 0 || *diastolik < 0) {
            printf("Tekanan darah tidak valid.\n");
        }
    }
    while (*sistolik <= 0 || *diastolik <= 0);

    do {
        printf("Detak jantung (bpm): ");
        scanf("%d", detak);

        if (*detak < 0) {
            printf("Detak jantung tidak valid.\n");
        }
    }
    while (*detak <= 0);

    do {
        printf("Saturasi oksigen (%%): ");
        scanf("%f", saturasi);

        if (*saturasi < 0) {
            printf("Saturasi oksigen tidak valid.\n");
        }
    }
    while (*saturasi <= 0);

    do {
        printf("Kadar gula darah (mg/dL): ");
        scanf("%d", gula);

        if (*gula < 0) {
            printf("Kadar gula darah tidak valid.\n");
        }
    }
    while (*gula <= 0);

    do {
        printf("Berat badan (kg): ");
        scanf("%f", berat);

        if (*berat < 0) {
            printf("Berat badan tidak valid.\n");
        }
    }
    while (*berat <= 0);

    do {
        printf("Tinggi badan (cm): ");
        scanf("%d", tinggi);

        if (*tinggi < 0) {
            printf("Tinggi badan tidak valid.\n");
        }
    }
    while (*tinggi <= 0);

    do {
        printf("Kadar kolesterol (mg/dL): ");
        scanf("%d", kolesterol);

        if (*kolesterol < 0) {
            printf("Kadar kolesterol tidak valid.\n");
        }
    }
    while (*kolesterol <= 0);

    do {
        printf("Kadar kolesterol LDL (mg/dL): ");
        scanf("%d", ldl);

        if (*ldl < 0) {
            printf("Kadar kolesterol LDL tidak valid.\n");
        }
    }
    while (*ldl <= 0);

    do {
        printf("Trombosit (x10^6/L): ");
        scanf("%d", trombosit);

        if (*trombosit < 0) {
            printf("Trombosit tidak valid.\n");
        }
    }
    while (*trombosit <= 0);
}

// Fungsi pendaftaran check-up
void DaftarCheckup(UserList *userList, Session *session, Queue *antrianDokter, Matrix *denahRumahSakit, int *indexDokter, int jumlahDokter) {
    if (!session->loggedIn || strcmp(GetRole(&session->currentUser), "Pasien") != 0) {
        printf("Akses ditolak. Login sebagai pasien terlebih dahulu.\n");
        return;
    }

    float suhu; int sistolik; int diastolik; int detak; float saturasi; int gula; float berat; int tinggi;
    int kolesterol; int ldl; int trombosit;

    // Input data medis pasien
    InputDataMedis(&suhu, &sistolik, &diastolik, &detak, &saturasi, &gula, &berat, &tinggi, &kolesterol, &ldl, &trombosit);

    // Masukkan data medis pasien ke dalam userList
    User *user = &session->currentUser;
    user->suhuTubuh = suhu;
    user->tekananDarahSistolik = sistolik;
    user->tekananDarahDiastolik = diastolik;
    user->detakJantung = detak;
    user->saturasiOksigen = saturasi;
    user->kadarGulaDarah = gula;
    user->beratBadan = berat;
    user->tinggiBadan = tinggi;
    user->kadarKolesterol = kolesterol;
    user->kadarKolesterolLDL = ldl;
    user->trombosit = trombosit;

    // Buat map baru yang isinya dokter:ruangan (ga perlu dihapus)
    Map ruanganDokter;
    initMap(&ruanganDokter);

    int dokterIndices[jumlahDokter]; // simpan indeks userList dokter
    int countDokter = 0;
    for (int i = 0; i < userList->count; i++) {
        if (strcmp(userList->users[i].role, "dokter") == 0) {
            int row, col;
            char namaRuangan[12];

            FindDokter(&denahRumahSakit, &row, &col, namaRuangan, userList->users[i].id);
            insertDokterMap(&ruanganDokter, userList->users[i].id, namaRuangan);

            dokterIndices[countDokter++] = i;
            if (countDokter >= jumlahDokter) break;
        }
    }

    // Tampilkan dokter yang tersedia dengan antrian masing-masing
    printf("Daftar dokter yang tersedia:\n");
    for (int i = 0; i < countDokter; i++) {
        int idx = dokterIndices[i];
        int dokterId = userList->users[idx].id;
        const char *ruangan = getMap(&ruanganDokter, dokterId);
        int panjangAntrian = antrianDokter[i].length;
        printf("%d. Dr. %s - %s (Antrian: %d orang)\n", i+1, userList->users[idx].username, ruangan ? ruangan : "-", panjangAntrian);
    }

    // Pilih dokter oleh pasien
    int pilihanDokter;
    printf("Pilih dokter (masukkan nomor): ");
    scanf("%d", &pilihanDokter);
    if (pilihanDokter < 1 || pilihanDokter > countDokter) {
        printf("Pilihan dokter tidak valid.\n");
        return;
    }
    pilihanDokter -= 1;  // ubah jadi indeks array

    // Antrian dokter yang dipilih
    Queue *queue = &antrianDokter[pilihanDokter];
    int idPasien = user->id;

    // Cek apakah pasien sudah ada di antrian
    Node *curr = queue->head;
    while (curr != NULL) {
        if (curr->data == idPasien) {
            printf("Pasien sudah terdaftar dalam antrian dokter ini.\n");
            return;
        }
        curr = curr->next;
    }

    // Masukkan pasien ke antrian dokter
    Node *nodePasien = createNode(idPasien);
    enqueue(queue, nodePasien);

    printf("Pendaftaran check-up berhasil. Pasien masuk ke antrian dokter %s.\n", userList->users[dokterIndices[pilihanDokter]].username);
}
#include "../header/checkup.h"
#include "../header/matrix.h"
#include "../header/dokter.h"
#include "../header/user.h"
#include "../header/manager.h"
#include <stdio.h>
#include <string.h>

void InputDataMedis(float *suhu, int *sistolik, int *diastolik, int *detak, float *saturasi, int *gula, float *berat, int *tinggi, int *kolesterol, int *trombosit)
{
    printf("Masukkan data medis:\n");
    do
    {
        printf("Suhu tubuh (°C): ");
        scanf("%f", suhu);

        if (*suhu <= 0)
        {
            printf("Suhu tidak valid.\n");
        }
    } while (*suhu <= 0);

    do
    {
        printf("Tekanan darah (sistolik dan diastolik): ");
        scanf("%d %d", sistolik, diastolik);

        if (*sistolik <= 0 || *diastolik <= 0)
        {
            printf("Tekanan darah tidak valid.\n");
        }
    } while (*sistolik <= 0 || *diastolik <= 0);

    do
    {
        printf("Detak jantung (bpm): ");
        scanf("%d", detak);

        if (*detak <= 0)
        {
            printf("Detak jantung tidak valid.\n");
        }
    } while (*detak <= 0);

    do
    {
        printf("Saturasi oksigen (%%): ");
        scanf("%f", saturasi);

        if (*saturasi <= 0)
        {
            printf("Saturasi oksigen tidak valid.\n");
        }
    } while (*saturasi <= 0);

    do
    {
        printf("Kadar gula darah (mg/dL): ");
        scanf("%d", gula);

        if (*gula <= 0)
        {
            printf("Kadar gula darah tidak valid.\n");
        }
    } while (*gula <= 0);

    do
    {
        printf("Berat badan (kg): ");
        scanf("%f", berat);

        if (*berat <= 0)
        {
            printf("Berat badan tidak valid.\n");
        }
    } while (*berat <= 0);

    do
    {
        printf("Tinggi badan (cm): ");
        scanf("%d", tinggi);

        if (*tinggi <= 0)
        {
            printf("Tinggi badan tidak valid.\n");
        }
    } while (*tinggi <= 0);

    do
    {
        printf("Kadar kolesterol (mg/dL): ");
        scanf("%d", kolesterol);

        if (*kolesterol <= 0)
        {
            printf("Kadar kolesterol tidak valid.\n");
        }
    } while (*kolesterol <= 0);

    do
    {
        printf("Trombosit (x10^6/L): ");
        scanf("%d", trombosit);

        if (*trombosit <= 0)
        {
            printf("Trombosit tidak valid.\n");
        }
    } while (*trombosit <= 0);
}

void DaftarCheckup(UserList *userList, Session *session, Matrix *denahRumahSakit)
{
    if (!session->loggedIn || strcmp(GetRole(&session->currentUser), "pasien") != 0)
    {
        printf("Akses ditolak. Login sebagai pasien terlebih dahulu.\n");
        return;
    }

    int sudahTerdaftar = 0;
    for (int i = 0; i < denahRumahSakit->rows; i++)
    {
        for (int j = 0; j < denahRumahSakit->cols; j++)
        {
            Ruangan *ruangan = &denahRumahSakit->data[i][j];
            Node *currentPasien = ruangan->antrianPasien.head;
            while (currentPasien != NULL)
            {
                if (currentPasien->data == session->currentUser.id)
                {
                    sudahTerdaftar = 1;
                    break;
                }
                currentPasien = currentPasien->next;
            }
            if (sudahTerdaftar)
                break;
        }
        if (sudahTerdaftar)
            break;
    }
    if (sudahTerdaftar)
    {
        printf("Anda sudah terdaftar dalam antrian check-up!\n");
        return;
    }

    float suhu;
    int sistolik;
    int diastolik;
    int detak;
    float saturasi;
    int gula;
    float berat;
    int tinggi;
    int kolesterol;
    int trombosit;

    InputDataMedis(&suhu, &sistolik, &diastolik, &detak, &saturasi, &gula, &berat, &tinggi, &kolesterol, &trombosit);

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
    user->trombosit = trombosit;

    int dokterCount = 0;
    int dokterList[userList->count];

    printf("\nDaftar Dokter yang Tersedia:");

    for (int i = 0; i < userList->count; i++)
    {
        if (strcmp(userList->users[i].role, "dokter") == 0)
        {
            // Cari lokasi ruangan dokter
            int row, col;
            char namaRuangan[12];
            FindDokter(denahRumahSakit, &row, &col, namaRuangan, userList->users[i].id);

            // cari length queue
            Ruangan *ruangan = GetRuangan(denahRumahSakit, row, col);
            int antrian = (ruangan != NULL) ? ruangan->antrianPasien.length : 0;

            printf("\n%d. Dr. %s - %s (Antrian: %d)",
                   dokterCount + 1,
                   userList->users[i].username,
                   namaRuangan,
                   antrian);

            dokterList[dokterCount] = i;
            dokterCount++;
        }
    }

    // pilih dokter
    int pilihanDokter;
    printf("\nPilih dokter (1-%d): ", dokterCount);
    scanf("%d", &pilihanDokter);

    if (pilihanDokter < 1 || pilihanDokter > dokterCount)
    {
        printf("Pilihan tidak valid!\n");
        return;
    }
    pilihanDokter--; // convert jadi index

    // cari ruangan dokter yang dipilih.
    int selectedDokterId = userList->users[dokterList[pilihanDokter]].id;

    int row, col;
    char namaRuangan[12];
    FindDokter(denahRumahSakit, &row, &col, namaRuangan, selectedDokterId);

    Ruangan *targetRuangan = GetRuangan(denahRumahSakit, row, col);
    if (targetRuangan == NULL)
    {
        printf("Error: Dokter tidak memiliki ruangan!\n");
        return;
    }

    // cek apakah pasien sudah berada didalam queue
    Node *curr = targetRuangan->antrianPasien.head;
    while (curr != NULL)
    {
        if (curr->data == user->id)
        {
            printf("Anda sudah terdaftar dalam antrian ini!\n");
            return;
        }
        curr = curr->next;
    }

    Node *newNode = createNode(user->id);
    enqueue(&targetRuangan->antrianPasien, newNode);

    printf("\nPendaftaran berhasil! Anda berada di posisi antrian ke-%d di ruangan %s\n", targetRuangan->antrianPasien.length, targetRuangan->namaRuangan);
}

void LihatAntrianSaya(UserList *userList, Session *session, Matrix *denahRumahSakit)
{
    if (!session->loggedIn || strcmp(session->currentUser.role, "pasien") != 0)
    {
        printf("\nError: Akses ditolak. Login sebagai pasien terlebih dahulu!\n");
        return;
    }

    int pasienId = session->currentUser.id;
    int found = 0;

    for (int i = 0; i < denahRumahSakit->rows; i++)
    {
        for (int j = 0; j < denahRumahSakit->cols; j++)
        {
            Ruangan *ruangan = &denahRumahSakit->data[i][j];

            Node *curr = ruangan->antrianPasien.head;
            int posisi = 1;

            while (curr != NULL)
            {
                if (curr->data == pasienId)
                {
                    int dokterId = ruangan->dokter;
                    User dokter = GetUserById(userList, dokterId);

                    // if (dokter.id == -1)
                    // {
                    //     printf("\nError: Data dokter tidak valid!\n");
                    //     return;
                    // }

                    if (posisi - ruangan->kapasitasRuangan <= 0 || ruangan->antrianPasien.length - ruangan->kapasitasRuangan <= 0)
                    {
                        printf("\nAnda sedang berada di dalam ruangan dokter!");
                    }
                    else
                    {
                        printf("\nStatus Antrian Anda:");
                        printf("\nDokter  : Dr. %s", dokter.username);
                        printf("\nRuangan : %s", ruangan->namaRuangan);
                        printf("\nPosisi  : %d dari %d", posisi - ruangan->kapasitasRuangan, ruangan->antrianPasien.length - ruangan->kapasitasRuangan);
                    }

                    found = 1;
                    return;
                }
                curr = curr->next;
                posisi++;
            }
        }
    }

    if (!found)
    {
        printf("\nAnda belum terdaftar dalam antrian check-up!\n");
        printf("Silakan daftar terlebih dahulu.\n");
    }
}
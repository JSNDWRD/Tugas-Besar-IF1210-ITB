#include "../header/ngobatin.h"

void CreateObatMap(ObatMap *obatMap);

void CreateObatList(ObatMap *obatMap);

int ObatMapLength(ObatMap obatMap);

int ObatListLength(ObatList obatList);

ObatEntry GetObatEntry(ObatMap obatMap, int i);

Obat GetObat(ObatList obatList, int i);

Obat GetObatById(ObatList obatList, int idx)
{
    for (int i = 0; i < obatList.length; i++)
    {
        if (obatList.obats[i].id == idx)
        {
            return obatList.obats[i];
        }
    }
    Obat tidakDitemukan;
    tidakDitemukan.id = -1;
    strcpy(tidakDitemukan.nama, "");
    return tidakDitemukan;
}

Obat GetObatByName(ObatList obatList, const char *namaPenyakit)
{
    for (int i = 0; i < obatList.length; i++)
    {
        if (strcmp(obatList.obats[i].nama, namaPenyakit) == 0)
        {
            return obatList.obats[i];
        }
    }
    Obat tidakDitemukan;
    tidakDitemukan.id = -1;
    strcpy(tidakDitemukan.nama, "");
    return tidakDitemukan;
}

int SearchObatIndex(ObatMap obatMap, const char *penyakit);

void PrintObat(ObatMap obatMap, int penyakitId, ObatList obatList, const char *namaPenyakit, char arrayUrutanObat[][500], User *pasien)
{
    if (penyakitId == -1)
    {
        printf("Penyakit %s tidak ditemukan.\n", namaPenyakit);
        return;
    }

    int idx = -1;
    for (int i = 0; i < obatMap.length; i++)
    {
        if (obatMap.buffer[i].penyakitId == penyakitId)
        {
            idx = i;
            break;
        }
    }
    if (idx == -1)
    {
        printf("Tidak ada obat untuk penyakit %s.\n", namaPenyakit);
        return;
    }

    int panjangNgobat = 0;
    for (int i = 0; i < obatMap.buffer[idx].urutan; i++)
    {
        if (obatMap.buffer[idx].obatId[i] != -1)
        {
            panjangNgobat++;
        }
    }

    pasien->jumlahNgobat = panjangNgobat;

    char namaObat[1000][500];
    int idxObat[1000];
    int count = 0;

    printf("Obat untuk penyakit %s:\n", namaPenyakit);
    for (int i = 0; i < obatMap.buffer[idx].urutan; i++)
    {
        int obatId = obatMap.buffer[idx].obatId[i];
        if (obatId == -1)
            continue;

        for (int j = 0; j < obatList.length; j++)
        {
            if (obatList.obats[j].id == obatId)
            {
                idxObat[count] = i + 1;
                strcpy(namaObat[count], obatList.obats[j].nama);

                int obatSudahAda = 0;
                for (int k = 0; k < pasien->jumlahObat && !obatSudahAda; k++)
                {
                    if (pasien->obat[k] == obatList.obats[j].id)
                    {
                        obatSudahAda = 1;
                    }
                }

                if (!obatSudahAda)
                {
                    pasien->obat[pasien->jumlahObat++] = obatList.obats[j].id;
                }
                count++;
                break;
            }
        }
    }

    for (int i = 0; i < count; i++)
    {
        strcpy(arrayUrutanObat[i], namaObat[i]);
        pasien->urutanNgobat[i] = GetObatByName(obatList, namaObat[i]).id;
        printf("%d. %s\n", idxObat[i], namaObat[i]);
    }
}

void LoadObat(ObatList *obatList, char *inputFolder)
{
    char folderName[100];
    strcpy(folderName, inputFolder);
    strcat(folderName, "/obat.csv");
    FILE *fObatList = fopen(folderName, "r");

    // Inisialisasi jumlah user
    int count = 0;

    if (fObatList == NULL)
    {
        printf("\"%s\" tidak ditemukan.\n", folderName);
    }

    char baris[1024];

    // Skip baris header
    fgets(baris, sizeof(baris), fObatList);

    while (fgets(baris, sizeof(baris), fObatList))
    {
        Obat obat;

        // i sebagai iterator while-loop, current sebagai indeks sementara, dan kolomData sebagai indeks akses data per kolom (0: id, 1: username, dst...)
        int i = 0, current = 0, kolomData = 0;
        char currentData[100];

        while (baris[i] != '\0' && baris[i] != '\n')
        {
            if (baris[i] == ';' || baris[i] == ',')
            { // Cek Separator
                currentData[current] = '\0';
                switch (kolomData)
                {
                case 0:
                    obat.id = (strlen(currentData) > 0) ? atoi(currentData) : -1;
                    break;
                }
                current = 0;
                kolomData++;
            }
            else
            {
                if ((size_t)current < sizeof(currentData) - 1)
                {
                    currentData[current] = baris[i];
                }
                current++;
            }
            i++;
        }

        // Kolom Data terakhir
        currentData[current] = '\0';
        strncpy(obat.nama, strlen(currentData) > 0 ? currentData : "-", sizeof(obat.nama) - 1);
        obat.nama[sizeof(obat.nama) - 1] = '\0'; // pastikan null-terminated
        obatList->obats[count] = obat;
        count++;
    }
    obatList->length = count;
    fclose(fObatList);
}

void LoadObatMap(ObatMap *obatMap, char *inputFolder)
{
    char folderName[100];
    strcpy(folderName, inputFolder);
    strcat(folderName, "/obat_penyakit.csv");
    FILE *fObatMap = fopen(folderName, "r");

    if (fObatMap == NULL)
    {
        printf("\"%s\" tidak ditemukan.\n", folderName);
        return;
    }

    char baris[1024];
    fgets(baris, sizeof(baris), fObatMap); // skip header

    obatMap->banyakObat = 0;
    obatMap->length = 0;
    int banyakObat = 0;

    while (fgets(baris, sizeof(baris), fObatMap))
    {
        banyakObat++;
        int obatId = -1, penyakitId = -1, urutan = -1;
        int i = 0, current = 0, kolomData = 0;
        char currentData[100];

        while (baris[i] != '\0' && baris[i] != '\n')
        {
            if (baris[i] == ',' || baris[i] == ';')
            {
                currentData[current] = '\0';
                switch (kolomData)
                {
                case 0:
                    obatId = atoi(currentData);
                    break;
                case 1:
                    penyakitId = atoi(currentData);
                    break;
                case 2:
                    urutan = atoi(currentData);
                    break;
                }
                current = 0;
                kolomData++;
            }
            else
            {
                if ((size_t)current < sizeof(currentData) - 1)
                {
                    currentData[current] = baris[i];
                }
                current++;
            }
            i++;
        }

        currentData[current] = '\0';
        if (kolomData == 2)
        {
            urutan = atoi(currentData);
        }

        int idx = -1;
        for (int j = 0; j < obatMap->length; j++)
        {
            if (obatMap->buffer[j].penyakitId == penyakitId)
            {
                idx = j;
                break;
            }
        }
        if (idx == -1)
        {
            idx = obatMap->length++;
            obatMap->buffer[idx].penyakitId = penyakitId;
            for (int k = 0; k < 100; k++)
            {
                obatMap->buffer[idx].obatId[k] = -1;
                obatMap->buffer[idx].urutan = 0;
            }
        }
        obatMap->buffer[idx].obatId[urutan - 1] = obatId;
        if (obatMap->buffer[idx].urutan < urutan)
            obatMap->buffer[idx].urutan = urutan;
    }
    obatMap->banyakObat = banyakObat;
    fclose(fObatMap);
}

void SaveObat(char *folderAsal, char *folderTujuan)
{
    char pathAsal[256], pathTujuan[256], baris[1024];
    strcpy(pathAsal, folderAsal);
    strcpy(pathTujuan, folderTujuan);
    strcat(pathAsal, "/obat.csv");
    strcat(pathTujuan, "/obat.csv");
    FILE *fAsal = fopen(pathAsal, "r");
    FILE *fTujuan = fopen(pathTujuan, "w");
    while (fgets(baris, sizeof(baris), fAsal))
    {
        fputs(baris, fTujuan);
    }
    fclose(fAsal);
    fclose(fTujuan);
}

void MinumObat(ObatList obatList, User *user, char arrNamaObat[][500])
{
    if (user->jumlahObat == 0) {
        printf("Anda tidak memiliki obat di inventory\n");
    }
    else {
        // printf("============ DAFTAR OBAT ============\n");
        // for (int i = 0; i < session.currentUser.jumlahObat; i++)
        // {
        //     printf("%d. %s\n", i + 1, GetObatById(obatList, session.currentUser.obat[i]).nama);
        // }
        int N;
        do {
            printf("\n>>> Pilih obat untuk diminum: ");
            scanf("%d", &N);
            if (N > user->jumlahObat || N <= 0) {
                printf("Pilihan nomor tidak tersedia!\n");
            }
        } while (N > user->jumlahObat || N <= 0);
        
        printf("Obat berhasil diminum!\n");
        Push(&user->perut, GetObatById(obatList, user->obat[N - 1]));
        user->jumlahObatMasukPerut++;
        for (int i = N - 1; i < user->jumlahObat - 1; i++)
        {
            user->obat[i] = user->obat[i + 1];
        }
        user->jumlahObat--;
    }
}
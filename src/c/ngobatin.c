#include "../header/ngobatin.h"

void CreateObatMap(ObatMap *obatMap);

void CreateObatList(ObatMap *obatMap);

int ObatMapLength(ObatMap obatMap);

int ObatListLength(ObatList obatList);

ObatEntry GetObatEntry(ObatMap obatMap, int i);

Obat GetObat(ObatList obatList, int i);

int SearchObatIndex(ObatMap obatMap, const char *penyakit);

void PrintObat(ObatMap obatMap, const char *penyakit);

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
        strcpy(obat.nama, strlen(currentData) > 0 ? currentData : "-");

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

    obatMap->length = 0;

    while (fgets(baris, sizeof(baris), fObatMap))
    {
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
            urutan = atoi(currentData);

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
                obatMap->buffer[idx].obatId[k] = -1;
            obatMap->buffer[idx].urutan = 0;
        }
        obatMap->buffer[idx].obatId[urutan - 1] = obatId;
        if (obatMap->buffer[idx].urutan < urutan)
            obatMap->buffer[idx].urutan = urutan;
    }
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
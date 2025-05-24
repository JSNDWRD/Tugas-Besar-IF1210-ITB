#include "../header/diagnosis.h"

void LoadPenyakit(PenyakitList *penyakitList, char *inputFolder)
{
    char folderName[100];
    strcpy(folderName, inputFolder);
    strcat(folderName, "/penyakit.csv");
    FILE *fPenyakit = fopen(folderName, "r");

    // Inisialisasi jumlah penyakit
    int count = 0;

    if (fPenyakit == NULL)
    {
        printf("\"%s\" tidak ditemukan.\n", folderName);
    }

    char baris[1024];

    // Skip baris header
    fgets(baris, sizeof(baris), fPenyakit);

    while (fgets(baris, sizeof(baris), fPenyakit))
    {
        Penyakit penyakit;

        // i sebagai iterator while-loop, current sebagai indeks sementara, dan kolomData sebagai indeks akses data per kolom (0: id, 1: penyakitname, dst...)
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
                    penyakit.id = (strlen(currentData) > 0) ? atoi(currentData) : -1;
                    break;
                case 1:
                    if (strlen(currentData) > 0)
                        strcpy(penyakit.namaPenyakit, currentData);
                    else
                        strcpy(penyakit.namaPenyakit, "-");
                    break;
                case 2:
                    penyakit.suhuTubuhMin = (strlen(currentData) > 0) ? atof(currentData) : -1.0;
                    break;
                case 3:
                    penyakit.suhuTubuhMax = (strlen(currentData) > 0) ? atof(currentData) : -1.0;
                    break;
                case 4:
                    penyakit.tekananDarahSistolikMin = (strlen(currentData) > 0) ? atoi(currentData) : -1;
                    break;
                case 5:
                    penyakit.tekananDarahSistolikMax = (strlen(currentData) > 0) ? atoi(currentData) : -1;
                    break;
                case 6:
                    penyakit.tekananDarahDiastolikMin = (strlen(currentData) > 0) ? atoi(currentData) : -1;
                    break;
                case 7:
                    penyakit.tekananDarahDiastolikMax = (strlen(currentData) > 0) ? atoi(currentData) : -1;
                    break;
                case 8:
                    penyakit.detakJantungMin = (strlen(currentData) > 0) ? atoi(currentData) : -1;
                    break;
                case 9:
                    penyakit.detakJantungMax = (strlen(currentData) > 0) ? atoi(currentData) : -1;
                    break;
                case 10:
                    penyakit.saturasiOksigenMin = (strlen(currentData) > 0) ? atof(currentData) : -1.0;
                    break;
                case 11:
                    penyakit.saturasiOksigenMax = (strlen(currentData) > 0) ? atof(currentData) : -1.0;
                    break;
                case 12:
                    penyakit.kadarGulaDarahMin = (strlen(currentData) > 0) ? atoi(currentData) : -1;
                    break;
                case 13:
                    penyakit.kadarGulaDarahMax = (strlen(currentData) > 0) ? atoi(currentData) : -1;
                    break;
                case 14:
                    penyakit.beratBadanMin = (strlen(currentData) > 0) ? atof(currentData) : -1.0;
                    break;
                case 15:
                    penyakit.beratBadanMax = (strlen(currentData) > 0) ? atof(currentData) : -1.0;
                    break;
                case 16:
                    penyakit.tinggiBadanMin = (strlen(currentData) > 0) ? atoi(currentData) : -1;
                    break;
                case 17:
                    penyakit.tinggiBadanMax = (strlen(currentData) > 0) ? atoi(currentData) : -1;
                    break;
                case 18:
                    penyakit.kadarKolesterolMin = (strlen(currentData) > 0) ? atoi(currentData) : -1;
                    break;
                case 19:
                    penyakit.kadarKolesterolMax = (strlen(currentData) > 0) ? atoi(currentData) : -1;
                    break;
                case 20:
                    penyakit.trombositMin = (strlen(currentData) > 0) ? atoi(currentData) : -1;
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

        // Kolom Data trombosit
        currentData[current] = '\0';
        penyakit.trombositMax = strlen(currentData) > 0 ? atoi(currentData) : -1;

        penyakitList->penyakit[count] = penyakit;
        count++;
    }
    penyakitList->nEff = count;
    fclose(fPenyakit);
}

void Diagnosis(User user, PenyakitList penyakitList, char *namaPenyakit)
{
    for (int i = 0; i < penyakitList.nEff; i++)
    {
        Penyakit *p = &penyakitList.penyakit[i];
        int check = 1;

        if (user.suhuTubuh != -1.0f &&
            (user.suhuTubuh < p->suhuTubuhMin || user.suhuTubuh > p->suhuTubuhMax))
        {
            check = 0;
        }

        if (check && user.tekananDarahSistolik != -1 &&
            (user.tekananDarahSistolik < p->tekananDarahSistolikMin ||
             user.tekananDarahSistolik > p->tekananDarahSistolikMax))
        {
            check = 0;
        }

        if (check && user.tekananDarahDiastolik != -1 &&
            (user.tekananDarahDiastolik < p->tekananDarahDiastolikMin ||
             user.tekananDarahDiastolik > p->tekananDarahDiastolikMax))
        {
            check = 0;
        }

        if (check && user.detakJantung != -1 &&
            (user.detakJantung < p->detakJantungMin || user.detakJantung > p->detakJantungMax))
        {
            check = 0;
        }

        if (check && user.saturasiOksigen != -1.0f &&
            (user.saturasiOksigen < p->saturasiOksigenMin ||
             user.saturasiOksigen > p->saturasiOksigenMax))
        {
            check = 0;
        }

        if (check && user.kadarGulaDarah != -1 &&
            (user.kadarGulaDarah < p->kadarGulaDarahMin ||
             user.kadarGulaDarah > p->kadarGulaDarahMax))
        {
            check = 0;
        }

        if (check && user.beratBadan != -1.0f &&
            (user.beratBadan < p->beratBadanMin || user.beratBadan > p->beratBadanMax))
        {
            check = 0;
        }

        if (check && user.tinggiBadan != -1 &&
            (user.tinggiBadan < p->tinggiBadanMin || user.tinggiBadan > p->tinggiBadanMax))
        {
            check = 0;
        }

        if (check && user.kadarKolesterol != -1 &&
            (user.kadarKolesterol < p->kadarKolesterolMin ||
             user.kadarKolesterol > p->kadarKolesterolMax))
        {
            check = 0;
        }

        if (check && user.trombosit != -1 &&
            (user.trombosit < p->trombositMin || user.trombosit > p->trombositMax))
        {
            check = 0;
        }

        if (check)
        {
            strcpy(namaPenyakit, p->namaPenyakit);
            // printf("%s terdiagnosa penyakit %s!\n", user.username, p->namaPenyakit);
            return;
        }
    }
    strcpy(namaPenyakit, ""); // Jika tidak ditemukan penyakit apa pun
    // printf("%s tidak terdiagnosis penyakit apapun!\n", user.username);
}

void SearchRuangan(int doctorId, Matrix *denahHospital, int *indeksRuangan)
{
    int found = 0;
    for (int i = 0; i < denahHospital->rows; i++)
    {
        for (int j = 0; j < denahHospital->cols; j++)
        {
            if (doctorId == GetRuangan(denahHospital, i, j)->dokter)
            {
                indeksRuangan[0] = i;
                indeksRuangan[1] = j;
                found = 1;
                break;
            }
        }
        if (found)
        {
            break;
        }
    }
    if (!found)
    {
        indeksRuangan[0] = -1;
        indeksRuangan[1] = -1;
    }
}

// void ShiftAntrianRuangan(Matrix* denahHospital, Ruangan* currentRuangan){
//     for(int i = 1; i < currentRuangan->jumlahPasien; i++){
//         currentRuangan->pasien[i-1] = currentRuangan->pasien[i];
//     }
//     currentRuangan->jumlahPasien--;
//     currentRuangan->pasien[currentRuangan->jumlahPasien] = 0;
// }

int GetPenyakitID(PenyakitList penyakitList, char *namaPenyakit)
{
    for (int i = 0; i < penyakitList.nEff; i++)
    {
        if (strcmp(penyakitList.penyakit[i].namaPenyakit, namaPenyakit) == 0)
        {
            return penyakitList.penyakit[i].id;
        }
    }
    return -1;
}

void SavePenyakit(char *folderAsal, char *folderTujuan)
{
    char pathAsal[256], pathTujuan[256], baris[1024];
    char pathAsal1[256], pathTujuan1[256], baris1[1024];
    strcpy(pathAsal, folderAsal);
    strcpy(pathTujuan, folderTujuan);
    strcat(pathAsal, "/obat_penyakit.csv");
    strcat(pathTujuan, "/obat_penyakit.csv");
    FILE *fAsal = fopen(pathAsal, "r");
    FILE *fTujuan = fopen(pathTujuan, "w");
    while (fgets(baris, sizeof(baris), fAsal) != NULL)
    {
        fputs(baris, fTujuan);
    }
    fclose(fAsal);
    fclose(fTujuan);

    strcpy(pathAsal1, folderAsal);
    strcpy(pathTujuan1, folderTujuan);
    strcat(pathAsal1, "/penyakit.csv");
    strcat(pathTujuan1, "/penyakit.csv");
    FILE *fAsal1 = fopen(pathAsal1, "r");
    FILE *fTujuan1 = fopen(pathTujuan1, "w");
    while (fgets(baris1, sizeof(baris1), fAsal1) != NULL)
    {
        fputs(baris1, fTujuan1);
    }
    fclose(fAsal1);
    fclose(fTujuan1);
}

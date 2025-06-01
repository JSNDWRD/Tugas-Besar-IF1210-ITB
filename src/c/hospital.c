#include "../header/hospital.h"

void LoadConfig(Matrix *denahHospital, char *inputFolder, UserList *userList)
{
    char inputPath[50];
    strcpy(inputPath, inputFolder);
    strcat(inputPath, "/config.txt");
    FILE *fDenah = fopen(inputPath, "r");

    if (fDenah == NULL)
    {
        perror("FILE config.txt kosong\n");
    }

    char baris[1024];

    // memeriksa baris pertama yang berisi baris dan kolom
    fgets(baris, sizeof(baris), fDenah);

    int i = 0, count = 0, temp = 0;
    while (baris[i] != '\0' && baris[i] != '\n')
    {
        if (baris[i] >= '0' && baris[i] <= '9')
        {
            temp = temp * 10 + (baris[i] - '0');
        }
        else
        {
            if (count == 0)
                denahHospital->rows = temp;
            else if (count == 1)
                denahHospital->cols = temp;
            count++;
            temp = 0;
        }
        i++;
    }

    // isi nama ruangan sesuai kolom dan baris
    InisialisasiNamaRuangan(denahHospital);

    // memeriksa baris ke dua yg berisi kapasitas
    fgets(baris, sizeof(baris), fDenah);

    int kapasitasAntrian = 0, kapasitasRuangan = 0, j = 0;
    temp = 0, count = 0;

    while (baris[j] != '\0' && baris[j] != '\n')
    {
        if (baris[j] >= '0' && baris[j] <= '9')
        {
            temp = temp * 10 + (baris[j] - '0');
        }
        else
        {
            if (count == 0)
                kapasitasRuangan = temp;
            else if (count == 1)
                kapasitasAntrian = temp;
            count++;
            temp = 0;
        }
        j++;
    }

    // assign kapasitas untuk tiap kamar (semuanya sama)
    for (int i = 0; i < denahHospital->rows; i++)
    {
        for (int j = 0; j < denahHospital->cols; j++)
        {
            denahHospital->data[i][j].kapasitasRuangan = kapasitasRuangan;
            denahHospital->data[i][j].kapasitasAntrian = kapasitasAntrian;
            createQueue(&denahHospital->data[i][j].antrianPasien);
        }
    }

    // memeriksa baris ke 3-8 untuk mendapatkan id dosen,jumlah pasien, id pasien
    // int index = 0;
    for (int i = 0; i < denahHospital->rows; i++)
    {
        for (int j = 0; j < denahHospital->cols; j++)
        {
            /* array angka untuk menyimpan id sementara dari dokter dan para pasien
            Jika ada dokter angka[0] adalah id dokter dan angka[1-jumlahPasien+1] adalah id pasien
            */
            int angka[100], count = 0;
            fgets(baris, sizeof(baris), fDenah);
            int temp = 0, idx = 0;
            while (baris[idx] != '\0' && baris[idx] != '\n')
            {
                if (baris[idx] >= '0' && baris[idx] <= '9')
                {
                    temp = temp * 10 + (baris[idx] - '0');
                }
                else
                {
                    angka[count] = temp;
                    count++;
                    temp = 0;
                }
                idx++;
            }
            if (temp > 0)
            {
                angka[count++] = temp;
            }
            Ruangan *r = &denahHospital->data[i][j];

            if (angka[0] == 0 && count == 1)
            {
                r->dokter = -1;
                r->jumlahPasienDalamRuangan = 0;
                r->jumlahPasienDiAntrian = 0;
            }
            else
            {
                r->dokter = angka[0];
                r->jumlahPasienDalamRuangan = 0;
                r->jumlahPasienDiAntrian = 0;
                for (int p = 1; p <= r->kapasitasRuangan && p < count; p++)
                {
                    // Masukkan pasien yang ada di dalam ruangan
                    enqueue(&r->antrianPasien, createNode(angka[p]));
                    r->jumlahPasienDalamRuangan++;
                }
                for (int q = r->kapasitasRuangan + 1; q < count; q++)
                {
                    // Masukkan pasien yang ada di antrian luar ruangan
                    enqueue(&r->antrianPasien, createNode(angka[q]));
                    r->jumlahPasienDiAntrian++;
                }
            }
        }
    }

    fgets(baris, sizeof(baris), fDenah);
    int pasienInventory = 0, k = 0;
    while (baris[k] >= '0' && baris[k] <= '9')
    {
        pasienInventory = pasienInventory * 10 + (baris[k] - '0');
        k++;
    }
    userList->pasienDenganObat = pasienInventory;

    for (int i = 0; i < pasienInventory; i++)
    {
        fgets(baris, sizeof(baris), fDenah);
        int angka[100], cnt = 0, temp = 0, idx = 0;

        while (baris[idx] != '\0' && baris[idx] != '\n')
        {
            if (baris[idx] >= '0' && baris[idx] <= '9')
            {
                temp = temp * 10 + (baris[idx] - '0');
            }
            else if (temp > 0)
            {
                angka[cnt++] = temp;
                temp = 0;
            }
            idx++;
        }

        if (temp > 0)
        {
            angka[cnt++] = temp;
        }

        int indexinventory = -1;
        for (int i = 0; i < userList->count; i++)
        {
            if (userList->users[i].id == angka[0])
            {
                indexinventory = i;
                break;
            }
        }
        if (indexinventory == -1)
        {
            printf("User id %d tidak ada.\n", angka[0]);
            continue;
        }

        userList->users[indexinventory].jumlahObat = cnt - 1;
        for (int i = 1; i < cnt; i++)
        {
            userList->users[indexinventory].obat[i - 1] = angka[i];
        }
    }

    fgets(baris, sizeof(baris), fDenah);
    int pasienKondisiPerut = 0;
    k = 0;
    while (baris[k] >= '0' && baris[k] <= '9')
    {
        pasienKondisiPerut = pasienKondisiPerut * 10 + (baris[k] - '0');
        k++;
    }
    userList->pasienKondisiPerut = pasienKondisiPerut;

    for (int i = 0; i < pasienKondisiPerut; i++)
    {
        fgets(baris, sizeof(baris), fDenah);
        int angka[100], cnt = 0, temp = 0, idx = 0;

        while (baris[idx] != '\0' && baris[idx] != '\n')
        {
            if (baris[idx] >= '0' && baris[idx] <= '9')
            {
                temp = temp * 10 + (baris[idx] - '0');
            }
            else if (temp > 0)
            {
                angka[cnt++] = temp;
                temp = 0;
            }
            idx++;
        }

        if (temp > 0)
        {
            angka[cnt++] = temp;
        }

        int indexPerut = -1;
        for (int i = 0; i < userList->count; i++)
        {
            if (userList->users[i].id == angka[0])
            {
                indexPerut = i;
                break;
            }
        }
        if (indexPerut == -1)
        {
            printf("User id %d tidak ada.\n", angka[0]);
            continue;
        }
        userList->users[indexPerut].jumlahObatMasukPerut = cnt - 1;
        Stack *PerutPasien = &userList->users[indexPerut].perut;
        CreateEmptyStack(PerutPasien);
        for (int i = cnt - 1; i >= 1; i--)
        {
            Obat obat;
            obat.id = angka[i];
            Push(PerutPasien, obat);
        }
    }

    fclose(fDenah);
}

void LihatDenah(Matrix *denahHospital)
{
    int lebar = denahHospital->cols;
    int panjang = denahHospital->rows;
    // Header kolom angka
    printf(" ");
    for (int j = 0; j < lebar; j++)
    {
        printf("     %d", j + 1);
    }
    printf("\n");

    for (int i = 0; i < panjang; i++)
    {
        // Garis atas
        printf("   +");
        for (int j = 0; j < lebar; j++)
        {
            printf("-----+");
        }
        printf("\n");

        // Baris nama ruangan
        printf(" %c ", 'A' + i);
        for (int j = 0; j < lebar; j++)
        {
            printf("| %-4s", denahHospital->data[i][j].namaRuangan);
        }
        printf("|\n");
    }

    // Garis bawah
    printf("   +");
    for (int j = 0; j < lebar; j++)
    {
        printf("-----+");
    }
    printf("\n");
}

void UbahInput(char *input, int *row, int *col)
{
    *row = -1;
    // isi variabel baris
    if (input[0] >= 'A' && input[0] <= 'Z')
    {
        *row = input[0] - 'A';
    }
    else
    {
        return;
    }

    *col = 0;
    int i = 1;
    while (input[i] >= '0' && input[i] <= '9')
    {
        *col = (*col) * 10 + (input[i] - '0');
        i++;
    }
    *col -= 1;
}

void LihatRuangan(Matrix *denahHospital, char *input, UserList *userList)
{
    int row, col;
    UbahInput(input, &row, &col);

    if (row < 0 || row >= denahHospital->rows || col < 0 || col >= denahHospital->cols)
    {
        printf("Ruangan %s tidak ditemukan.\n", input);
        return;
    }

    // variable r yang menyimpan struktur data di ruangan yang sesuai input)
    Ruangan *r = GetRuangan(denahHospital, row, col);

    printf("--- Detail Ruangan %s ---\n", r->namaRuangan);
    printf("Kapasitas  : %d\n", r->kapasitasRuangan);

    char dokter[MAX_USERNAME_LENGTH] = "Tidak Ada";
    // Cari userList dengan role dokter dan id yang sesuai
    for (int i = 0; i < userList->count; i++)
    {
        if (userList->users[i].id == r->dokter)
        {
            if (strcmp(userList->users[i].role, "dokter") == 0)
            {
                strcpy(dokter, userList->users[i].username);
            }
            else
            {
                printf("ID %d bukanlah id dokter\n", userList->users[i].id);
            }
            break;
        }
    }
    if (strcmp(dokter, "Tidak Ada") == 0)
    {
        printf("Dokter     : -\n");
    }
    else
    {
        printf("Dokter     : %s\n", dokter);
    }

    if (((r->jumlahPasienDalamRuangan == 0) || strcmp(dokter, "Tidak Ada") == 0) || (r->jumlahPasienDalamRuangan == 1 && r->antrianPasien.head->data == 0))
    {
        printf("  Tidak ada pasien di dalam ruangan saat ini.\n");
    }
    else
    {
        // cari setiap pasien di dalam ruangan yang sesuai
        printf("Pasien di dalam ruangan : \n");
        Node *n = r->antrianPasien.head;
        int index = 1;
        int count = 0;

        while (n != NULL && count < r->jumlahPasienDalamRuangan)
        {
            // cari nama pasien berdasarkan id
            char pasien[MAX_USERNAME_LENGTH] = "Tidak Diketahui";
            for (int j = 0; j < userList->count; j++)
            {
                if (userList->users[j].id == n->data && strcmp(userList->users[j].role, "pasien") == 0)
                {
                    strcpy(pasien, userList->users[j].username);
                    break;
                }
            }

            printf("  %d. %s\n", index++, pasien);
            n = n->next;
            count++;
        }
    }

    printf("------------------------------\n");
}

void SaveConfig(Matrix *denahHospital, char *inputFolder, UserList *userList)
{
    char outputPath[256];
    strcpy(outputPath, inputFolder);
    strcat(outputPath, "/config.txt");
    FILE *fileConfig = fopen(outputPath, "w");
    if (fileConfig == NULL)
    {
        perror("Gagal membuka file config.txt");
        return;
    }

    // Mengisi baris 1: jumlah baris dan kolom
    fprintf(fileConfig, "%d %d\n", denahHospital->rows, denahHospital->cols);

    // Mengisi baris 2: kapasitas ruangan dan kapasitas antrian
    fprintf(fileConfig, "%d %d\n", denahHospital->data[0][0].kapasitasRuangan, denahHospital->data[0][0].kapasitasAntrian);

    // Mengisi baris 3-8 : isi tiap ruangan denagn id dokter dan pasien
    // karena ruangan masih statik, jadi isi ruangan berada pada baris 3-8
    for (int i = 0; i < denahHospital->rows; i++)
    {
        for (int j = 0; j < denahHospital->cols; j++)
        {
            Ruangan r = denahHospital->data[i][j];

            if (r.dokter == -1)
            {
                fprintf(fileConfig, "0\n"); // jika tidak ada dokter tulis 0 saja pada baris tanpa id pasien
            }
            else
            { // jika ada dokter di ruangan itu
                fprintf(fileConfig, "%d", r.dokter);

                Node *n = r.antrianPasien.head;
                int count = 0;

                // Tulis pasien dalam ruangan terlebih dahulu
                while (n != NULL && count < r.jumlahPasienDalamRuangan)
                {
                    fprintf(fileConfig, " %d", n->data);
                    n = n->next;
                    count++;
                }

                // Tulis pasien dalam antrean
                while (n != NULL)
                {
                    fprintf(fileConfig, " %d", n->data);
                    n = n->next;
                }

                fprintf(fileConfig, "\n");
            }
        }
    }

    // mengisi baris 9 : jumlah orang dengan inventory obat
    fprintf(fileConfig, "%d\n", userList->pasienDenganObat);

    for (int i = 0; i < userList->count; i++)
    {
        if (userList->users[i].jumlahObat > 0)
        {
            fprintf(fileConfig, "%d", userList->users[i].id);
            for (int j = 0; j < userList->users[i].jumlahObat; j++)
            {
                fprintf(fileConfig, " %d", userList->users[i].obat[j]);
            }
            fprintf(fileConfig, "\n");
        }
    }

    // mengisi baris jumlah pasien yang memiliki kondisi perut dengan obat
    fprintf(fileConfig, "%d\n", userList->pasienKondisiPerut);
    for (int i = 0; i < userList->count; i++)
    {
        if (userList->users[i].jumlahObatMasukPerut > 0)
        {
            fprintf(fileConfig, "%d", userList->users[i].id);
            Stack *PerutPasien = &userList->users[i].perut;
            for (int j = userList->users[i].jumlahObatMasukPerut - 1; j >= 0; j--)
            {
                fprintf(fileConfig, " %d", PerutPasien->obat[j].id);
            }
            fprintf(fileConfig, "\n");
        }
    }
    fclose(fileConfig);
}
#include "../header/hospital.h"

void LoadConfig(Matrix *denahHospital, char *inputFolder){
    strcat(inputFolder,"/config.txt");
    FILE *fDenah = fopen(inputFolder,"r");


    if (fDenah == NULL) {
        perror("FILE config.txt kosong\n");
    }

    char baris[1024]; 

    // memeriksa baris pertama yang berisi baris dan kolom 
    fgets(baris,sizeof(baris),fDenah);

    int i = 0,count = 0,temp=0;
    while(baris[i] != '\0' && baris[i] != '\n'){
        if(baris[i] >= '0' && baris[i] <= '9'){
            temp = temp * 10 + (baris[i] - '0');
        }else{
            if(count == 0) denahHospital->rows = temp;
            else denahHospital->cols = temp;
            count ++;
        }
        i++;
    }


    // memeriksa baris ke dua yg berisi kapasitas
    fgets(baris,sizeof(baris),fDenah);

    int kapasitas = 0,j = 0;
    while (baris[j] >= '0' && baris[j] <= '9') {
        kapasitas = kapasitas * 10 + (baris[j] - '0');
        j++;
    }
    // assign kapasitas untuk tiap kamar (semuanya sama)
    for(int i=0;i<denahHospital->rows;i++){
        for(int j=0;j<denahHospital->cols;j++){
            denahHospital->data[i][j].kapasitas = kapasitas;
        }
    }

    // memeriksa baris ke 3-8 untuk mendapatkan id dosen,jumlah pasien, id pasien
    // int index = 0;
    for (int i = 0; i < denahHospital->rows; i++) {
        for(int j=0; j<denahHospital->cols;j++){
            /* array angka untuk menyimpan id sementara dari dokter dan para pasien
            Jika ada dokter angka[0] adalah id dokter dan angka[1-jumlahpasien+1] adalah id pasien 
            */
            int angka[100], cnt = 0, temp = 0, index = 0;
            fgets(baris, sizeof(baris), fDenah);
            while (baris[index] != '\0' && baris[index] != '\n') {
                if (baris[index] >= '0' && baris[index] <= '9') {
                    temp = temp * 10 + (baris[index] - '0');
                } else if (temp > 0) {
                    angka[cnt] = temp;
                    cnt++;
                    temp = 0;
                }
                index++;
            }
            if (temp > 0) angka[cnt++] = temp;

            if (cnt == 0) {
                denahHospital->data[i][j].dokter = -1;
                denahHospital->data[i][j].jumlahpasien = 0;
            } else {
                denahHospital->data[i][j].dokter = angka[0];
                denahHospital->data[i][j].jumlahpasien = cnt - 1;
                for (int k = 1; k < cnt; k++) {
                    denahHospital->data[i][j].pasien[k - 1] = angka[k];
                }
            }
        }
    }
    
    fclose(fDenah);
}
/* Membaca file eksternal dan memasukkan data config ke dalam denahHospital */
void LihatDenah(Matrix *denahHospital) {
    InisialisasiNamaRuangan(denahHospital);
    int lebar = denahHospital->cols;
    int panjang = denahHospital->rows;

    // Header kolom angka
    printf("   ");
    for (int j = 0; j < lebar; j++) {
        printf("     %d", j + 1);
    }
    printf("\n");

    for (int i = 0; i < panjang; i++) {
        // Garis atas
        printf("   +");
        for (int j = 0; j < lebar; j++) {
            printf("-----+");
        }
        printf("\n");

        // Baris nama ruangan
        printf(" %c ", 'A' + i);
        for (int j = 0; j < lebar; j++) {
            printf("| %-4s", denahHospital->data[i][j].namaruangan);  // menggunakan field nama
        }
        printf("|\n");
    }

    // Garis bawah
    printf("   +");
    for (int j = 0; j < lebar; j++) {
        printf("-----+");
    }
    printf("\n");
}

void UbahInput(char *input, int *row, int *col) {
    int i = 0;
    while (input[i] != '\0') {
        // Cek jika ada huruf kapital diikuti angka (contoh: A1, B12)
        if (input[i] >= 'A' && input[i] <= 'Z' && input[i + 1] >= '0' && input[i + 1] <= '9') {
            *row = input[i] - 'A'; // konversi huruf ke indeks baris
            i++;
            *col = 0;

            // baca angka setelah huruf
            while (input[i] >= '0' && input[i] <= '9') {
                *col = (*col) * 10 + (input[i] - '0');
                i++;
            }

            (*col)--; // ubah sesuai index dari 0 (misal input A1 -> index kolom 0)
            return;
        }
        i++;
    }
}

void LihatRuangan(Matrix *denahHospital, char *input, UserList userlist) {
    int row, col;
    UbahInput(input, &row, &col);

    // Validasi posisi
    if (!(isRowValid(row, *denahHospital)) || !(isColsValid(col, *denahHospital))) {
        printf("Ruangan tidak ditemukan.\n");
        return;
    }

    // variable r yang menyimpan struktur data di ruangan yang sesuai input)
    Ruangan *r = GetElement(denahHospital, row, col);

    printf("--- Detail Ruangan %s ---\n", r->namaruangan);
    printf("Kapasitas  : %d\n", r->kapasitas);

    char dokter[MAX_USERNAME_LENGTH] = "Tidak Ada";
    //Cari userlist dengan role dokter dan id yang sesuai
    for (int i = 0; i < userlist.count; i++) {
        if (userlist.users[i].id == r->dokter && strcmp(userlist.users[i].role, "dokter") == 0) {
            strcpy(dokter, userlist.users[i].username);
            break;
        }
    }
    if(strcmp(dokter,"Tidak Ada") == 0){
        printf("Dokter     : -\n");
    }else{
        printf("Dokter     : %s\n", dokter);
    }

    if (r->jumlahpasien == 0) {
        printf("  Tidak ada pasien di dalam ruangan saat ini.\n");
    } else {
        // cari setiap pasien di dalam ruangan yang sesuai
        for (int i = 0; i < r->jumlahpasien; i++) {
            char pasien[MAX_USERNAME_LENGTH];
            for (int j = 0; j < userlist.count; j++) {
                if (userlist.users[j].id == r->pasien[i] && strcmp(userlist.users[j].role, "pasien") == 0) {
                    strcpy(pasien, userlist.users[j].username);
                    break;
                }
            }
            printf("  %d. %s\n", i + 1, pasien);
        }
    }

    printf("------------------------------\n");
}

void SaveConfig(Matrix denahHospital) {
    FILE *file = fopen("config.txt", "w"); 
    if (file == NULL) {
        perror("Gagal membuka file config.txt");
        return;
    }

    // Mengisi baris 1: jumlah baris dan kolom 
    fprintf(file, "%d %d\n", denahHospital.rows, denahHospital.cols);

    // Mengisi baris 2: kapasitas ruangan
    fprintf(file, "%d\n", denahHospital.data[0][0].kapasitas);

    // Mengisi baris 3-8 : isi tiap ruangan denagn id dokter dan pasien
    // karena ruangan masih statik, jadi isi ruangan berada pada baris 3-8 
    for (int i = 0; i < denahHospital.rows; i++) {
        for (int j = 0; j < denahHospital.cols; j++) {
            Ruangan r = denahHospital.data[i][j];
            if (r.dokter == -1) {
                fprintf(file, "0\n");  // jika tidak ada dokter tulis 0 saja pada baris tanpa id pasien
            } else { // jika ada dokter di ruangan itu
                fprintf(file, "%d", r.dokter);
                for (int k = 0; k < r.jumlahpasien; k++) {
                    fprintf(file, " %d", r.pasien[k]);
                }
                fprintf(file, "\n");
            }
        }
    }
    fclose(file);
    printf("Data berhasil disimpan ke config.txt\n");
}
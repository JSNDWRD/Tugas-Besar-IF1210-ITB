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
            temp = 0;
        }
        i++;
    }

    // isi nama ruangan sesuai kolom dan baris
    InisialisasiNamaRuangan(denahHospital);


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
    int lebar = denahHospital->cols;
    int panjang = denahHospital->rows;

    // Header kolom angka
    printf(" ");
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
    *row = -1;
    *col = -1;
    
    // isi variabel baris
    if (input[0] >= 'A' && input[0] <= 'Z') {
        *row = input[0] - 'A';
    } else if (input[0] >= 'a' && input[0] <= 'z') {
        *row = input[0] - 'a';
    } else {
        return;
    }

    *col = 0;
    int i = 1;
    while (input[i] >= '0' && input[i] <= '9') {
        *col = (*col) * 10 + (input[i] - '0');
        i++;
    }
    *col -= 1;
}

void LihatRuangan(Matrix *denahHospital, char *input, UserList userList) {
    int row, col;
    UbahInput(input, &row, &col);

    // variable r yang menyimpan struktur data di ruangan yang sesuai input)
    Ruangan *r = GetElement(denahHospital, row, col);

    printf("--- Detail Ruangan %s ---\n", r->namaruangan);
    printf("Kapasitas  : %d\n", r->kapasitas);

    char dokter[MAX_USERNAME_LENGTH] = "Tidak Ada";
    //Cari userList dengan role dokter dan id yang sesuai
    for (int i = 0; i < userList.count; i++) {
        if (userList.users[i].id == r->dokter){
            if(strcmp(userList.users[i].role, "dokter") == 0) {
                strcpy(dokter, userList.users[i].username);
            }else {
                printf("ID %d bukanlah id dokter\n",userList.users[i].id);
            }
            break;
        }
    }
    if(strcmp(dokter,"Tidak Ada") == 0){
        printf("Dokter     : -\n");
    }else{
        printf("Dokter     : %s\n", dokter);
    }


    if ((r->jumlahpasien == 0) || strcmp(dokter,"Tidak Ada") == 0){
        printf("  Tidak ada pasien di dalam ruangan saat ini.\n");
    } else {
        // cari setiap pasien di dalam ruangan yang sesuai
        printf("Pasien di dalam ruangan : \n");
        for (int i = 0; i < r->jumlahpasien; i++) {
            char pasien[MAX_USERNAME_LENGTH];
            for (int j = 0; j < userList.count; j++) {
                if (userList.users[j].id == r->pasien[i] && strcmp(userList.users[j].role, "pasien") == 0) {
                    if(strcmp(userList.users[j].role, "pasien") == 0){
                        strcpy(pasien, userList.users[j].username);
                    }else{
                        printf("ID %d bukanlah id pasien\n",userList.users[j].id);
                    }
                    break;
                }
            }
            printf("  %d. %s\n", i + 1, pasien);
        }
    }

    printf("------------------------------\n");
}

void SaveConfig(Matrix denahHospital) {
    FILE *file = fopen("file/config.txt", "w"); 
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
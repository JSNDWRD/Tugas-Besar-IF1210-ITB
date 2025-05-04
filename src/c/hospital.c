#include "hospital.h"

void LoadConfig(Matrix *denahHospital){
    
    FILE *fDenah = fopen("./src/file/config.txt","r");

    // Inisialisasi jumlah user
    int count = 0;

    if (fDenah == NULL) {
        perror("FILE config.txt kosong\n");
    }

    char baris[1024]; 

    // Algorithm In Progress
    
    fclose(fDenah);
}
/* Membaca file eksternal dan memasukkan data config ke dalam denahHospital */

void saveConfig(Matrix denahHospital);
/* Menyimpan matrix denahHospital ke dalam file eksternal config.txt */
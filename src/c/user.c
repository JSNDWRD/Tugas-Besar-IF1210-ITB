#include "../header/user.h"

void LoadUsers(UserList *userList){
    FILE *fUserList = fopen("./src/file/user.csv","r");
    
    // Inisialisasi index awal dan jumlah 
    int count = 0;

    if (fUserList == NULL) {
        perror("FILE user.csv kosong\n");
    }

    char baris[1024]; 
    // Skip baris header
    fgets(baris, sizeof(baris), fUserList);

    while(fgets(baris,sizeof(baris),fUserList)){
        // Algoritma untuk menyimpan data user
        // Work in progress...
        count++;
    }
    userList->count = count;
    fclose(fUserList);
}
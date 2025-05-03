#include <stdio.h>
#include "../header/denah.h"

void LihatDenah(){
    FILE *Denahlist = fopen("../file/config.txt","r");

    if (Denahlist == NULL) {
        perror("FILE user.csv kosong\n");
    }

    char baris[1024];

    int lebar,panjang,temp=0;

    // memeriksa baris pertama yaitu panjang dan lebar dari rumah sakit
    fgets(baris,sizeof(baris),Denahlist);

    int i = 0,count = 0;
    while(baris[i] != '\0' && baris[i] != '\n'){
        if(baris[i] >= '0' && baris[i] <= '9'){
            temp = baris[i] - '0';
        }else{
            if(count == 0) panjang = temp;
            else lebar = temp;
            count ++;
        }
        i++;
    }

    if (count == 1) {
        lebar = temp;
    }

    // print denah rumah sakit

    for(int i=1;i<=lebar;i++){
        printf("     %d",i);
    }
    printf("\n");

    for(int i=0;i<panjang;i++){
        //print garis atas
        printf("  +");
        for(int j=1;j<= lebar;j++){
            printf("-----+");
        }
        printf("\n");

        //print nama ruangan
        printf("%c ",'A'+i);
        for(int j=0;j<lebar;j++){
            printf("| %c%d  ",'A'+i,j+1);
        }
        printf("|\n");
    }

    printf("  +");
    for(int j=1;j<= lebar;j++){
        printf("-----+");
    }
    printf("\n");

    fclose(Denahlist);
}

int main() {
    printf("== Test Fungsi LihatDenah ==\n\n");
    LihatDenah();
    return 0;
}

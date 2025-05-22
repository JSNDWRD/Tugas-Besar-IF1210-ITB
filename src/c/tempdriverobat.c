#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../header/obat.h"
#include "../header/load.h"
#include "../header/kamus.h"

int main(){
    //cuma buat ngetest, sifatnya sementara, nanti disesuain lagi sama fitur lain
    ListObat inventory;
    CreateListDin(&inventory, 25);  
    Stack perut;
    CreateEmptyStack(&perut);
    Stack urutan;
    CreateEmptyStack(&urutan);
    LoadObatFromCSV(&inventory, &urutan, "obat.csv");

    char input[50];
    scanf("%s", input);
    while(strcmp(input,"UDAH")!=0){
        if(strcmp(input,"MINUM_OBAT")==0){
            MinumObat(&inventory, &perut);
            printf("Current isi inventory:\n");
            printList(inventory);
            printf("\n");
            printf("Current isi perut:\n");
            printStackObat(perut);
            printf("\n");
        }
        else if(strcmp(input,"MINUM_PENAWAR")==0){
            MinumPenawar(&inventory, &perut);
            printf("Current isi inventory:\n");
            printList(inventory);
            printf("\n");
            printf("Current isi perut:\n");
            printStackObat(perut);
            printf("\n");
        }
        else if(strcmp(input,"PULANGDOK")==0){
            PulangDok(inventory, urutan, perut);
        }
        scanf("%s", input);
    }

    dealocateList(&inventory);
}
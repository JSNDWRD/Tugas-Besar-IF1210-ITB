#include "stack.h"
#include "listObat.h"
#include "boolean.h"
#include <string.h>
#include <stdio.h>

//BELUM FIX
void MinumObat(ListObat *l, Stack *perut){
    Obat obatDiminum;
    int pilihan;

    printList(*l);
    
    printf("Pilih obat untuk diminum: ");
    scanf("%d", &pilihan);
    while(!isIdxEff(*l, pilihan-1)){
        printf("Pilihan nomor tidak tersedia!\n\n");
        printf("Pilih obat untuk diminum: ");
        scanf("%d", &pilihan);
    }

    deleteAt(l, obatDiminum, pilihan-1);
    push(perut, obatDiminum);

    printf("GLEKGLEKGLEK... %s berhasil diminum!!!\n", obatDiminum);
}

void MinumPenawar(Stack *perut, ListObat *l){
    if(isStackEmpty(*perut)){
        printf("Perut kosong!! Belum ada obat yang dimakan.\n");
    }
    else{
        Obat muntah;
        pop(perut, &muntah);
        insertLast(l, muntah);
        printf("Uwekkk!!! %s keluar dan kembali ke inventory\n", muntah);
    }
}

void PulangDok(ListObat l, Stack urutan, Stack perut){
    printf("Dokter sedang memeriksa keadaanmu... \n\n");

    //case blm diagnosed 

    //case blm habisin obat
    if(!isListEmpty(l)){
        printf("Masih ada obat yang belum kamu habiskan, minum semuanya dulu yukk!\n");
    }

    else{
        //KASUS 3: Pasien sudah menghabiskan obat, namun terdapat urutan yang salah dalam konsumsinya
        if(!isStackEqual(urutan,perut)){
            printf("Maaf, tapi kamu masih belum bisa pulang!\n\n");
            printf("Urutan peminuman obat yang diharapkan:\n");
            printStackObat(urutan);
            printf("\n");
            printf("Urutan obat yang kamu minum:\n");
            printStackObat(perut);
            printf("\n");
            printf("Silahkan kunjungi dokter untuk meminta penawar yang sesuai !");
        }

        //KASUS 4: Pasien sudah menghabiskan obat, dan semuanya valid.
        else{
            printf("KASUS 4: Pasien sudah menghabiskan obat, dan semuanya valid.");
        }
    }
}
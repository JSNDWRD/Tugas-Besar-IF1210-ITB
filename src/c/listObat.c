#include "../header/kamus.h"
#include "../header/listObat.h"

//MASIH BISA BERUBAH
void CreateListDin(ListObat *l, int capacity){
    l->buffer = (Obat*) malloc(capacity * sizeof(Obat));
    l->capacity = capacity;
    l->nEff = 0;
} 

void dealocateList(ListObat *l){
    free(l->buffer);
    l->buffer = NULL;
    l->capacity = 0;
    l->nEff = 0;
}
   
boolean isIdxValid(ListObat l, int i){
    return (i>=0 && i<l.capacity);
}

boolean isIdxEff(ListObat l, int i){
    return (i>=0 && i<l.nEff);
}

boolean isListEmpty(ListObat l){
    return l.nEff==0;
}
   
boolean isListFull(ListObat l){
    return l.nEff==l.capacity;
}

void readList(ListObat *l){}

void printList(ListObat l){
    printf("============ DAFTAR OBAT ============\n");
    for(int i=0; i<l.nEff; i++){
        printf("%d. %s\n", i+1, l.buffer[i]);
    }
}

int indexOf(ListObat l, Obat val){
    for(int i=0; i<l.nEff; i++){
        if(strcmp(l.buffer[i],val)==0){
            return i;
        }
    }
    return IDX_UNDEF;
}

void insertLast(ListObat *l, Obat val){
    if(!isListFull(*l)){
        strncpy(l->buffer[l->nEff], val, MAX_OBAT_LENGTH);
        l->nEff++;
    }
}

void insertAt(ListObat *l, Obat val, int idx){
    if(isIdxEff(*l,idx)){
        l->nEff++;
        for(int i=l->nEff-1; i>idx; i--){
            strncpy(l->buffer[i],l->buffer[i-1],MAX_OBAT_LENGTH);
        }
        strncpy(l->buffer[idx], val, MAX_OBAT_LENGTH);
    }
}

void deleteLast(ListObat *l, Obat *val){
    if(!isListEmpty(*l)){
        strncpy(*val, l->buffer[l->nEff-1], MAX_OBAT_LENGTH);
        l->nEff--;
    }
}

void deleteAt(ListObat *l, Obat *val, int idx){
    if(isIdxEff(*l,idx)){
        strncpy(*val, l->buffer[idx], MAX_OBAT_LENGTH);
        for(int i=idx; i<l->nEff-1; i++){
            strncpy(l->buffer[i],l->buffer[i+1],MAX_OBAT_LENGTH);
        }
        l->nEff--;
    }
}

void expandList(ListObat *l, int num){
    l->capacity+=num;
    l->buffer = realloc(l->buffer, l->capacity * sizeof(Obat));
}

void shrinkList(ListObat *l, int num){
    l->capacity-=num;
    l->buffer = realloc(l->buffer, l->capacity * sizeof(Obat));
}

void compressList(ListObat *l){
    l->capacity = l->nEff;
    l->buffer = realloc(l->buffer, l->capacity * sizeof(Obat));
}
#ifndef KAMUS_h
#define KAMUS_h

#define boolean unsigned char
#define true 1
#define false 0

#define IDX_MIN 0
#define IDX_UNDEF -1
#define MAX_OBAT 100
#define MAX_OBAT_LENGTH 50
#define MAX_STACK_SIZE 100

typedef char Obat[MAX_OBAT_LENGTH];

typedef struct{
    Obat *buffer;
    int nEff;       
    int capacity;   
} ListObat;

typedef struct { 
    Obat obat[MAX_STACK_SIZE]; 
    int top;
} Stack;

typedef struct {
    int id;
    char nama[MAX_OBAT_LENGTH];
} DataObat;

#endif
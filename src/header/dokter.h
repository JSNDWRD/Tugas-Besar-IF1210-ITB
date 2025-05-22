#ifndef DOKTER_H
#define DOKTER_H

#include "user.h"

typedef struct Node
{
    int data;
    struct Node *next;
} Node;

typedef struct
{
    Node *head;
    Node *tail;
    int length;
} Queue;

// void initMap(Map *map);

// void insertMap(Map *map, int key, const char *ruangan);

// typedef struct {
//     int id;  // dokter ID
//     char namaRuangan[12];  // nama ruangan
// } Data;

// typedef struct {
//     Data data[100];
//     int size;
// } Map;

// node primitives

// create a new node based on an int value
Node *createNode(int value);

// membuat queue, head dan tailnya NULL, length 0
void createQueue(Queue *q);

// memasukkan node ke dalam queue
void enqueue(Queue *q, Node *newNode);

// mengeluarkan node dari queue, return int data, bukan node
int dequeue(Queue *q);

// cek apakah queue kosong
int isEmptyQueue(Queue q);

// hindarin memory leak
void freeQueue(Queue *q);

#endif
#include <stdio.h>
#include <stdlib.h>
#include "../header/dokter.h"
#include "../header/matrix.h"
#include "../header/manager.h"

Node *createNode(int value)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL)
    {
        printf("Memory error!\n");
        exit(1);
    }
    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}

void createQueue(Queue *q)
{
    q->head = NULL;
    q->tail = NULL;
    q->length = 0;
}

void enqueue(Queue *q, Node *newNode)
{
    if (newNode == NULL)
        return;

    newNode->next = NULL;
    if (q->tail == NULL)
    {
        q->head = newNode;
    }
    else
    {
        q->tail->next = newNode;
    }
    q->tail = newNode;
    q->length++;
}

int dequeue(Queue *q)
{
    if (isEmptyQueue(*q))
    {
        return -1;
    }

    Node *temp = q->head;
    int data = temp->data;

    q->head = q->head->next;
    if (q->head == NULL)
    {
        q->tail = NULL;
    }

    free(temp);
    q->length--;
    return data;
}

int isEmptyQueue(Queue q)
{
    return q.head == NULL;
}

void freeQueue(Queue *q)
{
    while (!isEmptyQueue(*q))
    {
        dequeue(q);
    }
}

// void initMap(Map *map) {
//     map->size = 0;
// }

// void insertDokterMap(Map *map, int key, const char *ruangan) {
//     // Cek apakah key sudah ada
//     for (int i = 0; i < map->size; i++) {
//         if (map->data[i].id == key) {
//             strcpy(map->data[i].namaRuangan, ruangan);
//             return;
//         }
//     }

//     // Masukkan entry baru
//     if (map->size < 100) {
//         map->data[map->size].id = key;
//         strcpy(map->data[map->size].namaRuangan, ruangan);
//         map->size++;
//     }
//     else {
//         printf("Map penuh!\n");
//     }
// }

// int pasienDalamRuangan(Ruangan *r) {
//     if (r->antrianPasien.length < r->kapasitasRuangan) {
//         return r->antrianPasien.length;
//     }
//     else return r->kapasitasRuangan;
// }
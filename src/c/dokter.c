#include "../header/dokter.h"
#include <stdlib.h>
#include <stdio.h>

Node createNode(int value) {
    Node node;
    node.data = value;
    node.next = NULL;
    return node;
}

void createQueue(Queue *q) {
    q->head = NULL;
    q->tail = NULL;
    q->length = 0;
}

void enqueue(Queue *q, Node *newNode) {
    newNode->next = NULL;
    if (q->tail == NULL) {
        q->head = newNode;
        q->tail = newNode;
    }
    else {
        q->tail->next = newNode;
        q->tail = newNode;
    }
    q->length++;
}

Node* dequeue(Queue *q) {
    if (isEmptyQueue(*q)) {
        return NULL;  // queue is empty
    }

    Node *temp = q->head;
    q->head = q->head->next;  // detach first node from queue

    if (q->head == NULL) {
        q->tail = NULL;  // queue is now empty
    }

    q->length--;
    temp->next = NULL;
    return temp;
}


int isEmptyQueue(Queue q) {
    return q.head == NULL;
}

void printQueue(Queue q) {
    Node *curr = q.head;
    printf("Queue: ");
    while (curr != NULL) {
        printf("%d ", curr->data);
        curr = curr->next;
    }
    printf("\n");
}

void initMap(Map *map) {
    map->size = 0;
}

void insertDokterMap(Map *map, int key, const char *ruangan) {
    // Cek apakah key sudah ada
    for (int i = 0; i < map->size; i++) {
        if (map->data[i].id == key) {
            strcpy(map->data[i].namaRuangan, ruangan);
            return;
        }
    }

    // Masukkan entry baru
    if (map->size < 100) {
        map->data[map->size].id = key;
        strcpy(map->data[map->size].namaRuangan, ruangan);
        map->size++;
    }
    else {
        printf("Map penuh!\n");
    }
}

#ifndef DOKTER_H
#define DOKTER_H

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
    Node *tail;
    int length;
} Queue;

void initMap(Map *map);

void insertMap(Map *map, int key, const char *ruangan);

typedef struct {
    int id;  // dokter ID
    char namaRuangan[12];  // nama ruangan
} Data;

typedef struct {
    Data data[100];
    int size;
} Map;

// node primitives

// create a new node based on an int value;
Node createNode(int value);


void createQueue(Queue *q);
void enqueue(Queue *q, Node *newNode);
Node* dequeue(Queue *q);
int isEmptyQueue(Queue q);
void printQueue(Queue q);

#endif
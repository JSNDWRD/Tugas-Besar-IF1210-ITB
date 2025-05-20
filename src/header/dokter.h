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

// node primitives

// create a new node based on an int value;
Node createNode(int value);


void createQueue(Queue *q);
void enqueue(Queue *q, Node *newNode);
Node* dequeue(Queue *q);
int isEmptyQueue(Queue q);
void printQueue(Queue q);

#endif
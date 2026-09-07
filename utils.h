#ifndef UTILS_H
#define UTILS_H

typedef struct Node {
    void *data;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
    Node *tail;
    int size;
} Queue;

typedef struct {
    Node *top;
} Stack;

void enqueue(Queue *q, void *data); //adauga la finalul cozii
void enqueue_front(Queue *q, void *data); //adauga la inceput
void* dequeue(Queue *q); //primul el
void push(Stack *s, void *data); //pune el in stiva
void* pop(Stack *s); // scoate ultimul el din stiva
void free_nodes(Node *head);

#endif
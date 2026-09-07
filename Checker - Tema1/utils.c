/* VIERU Ana 324CC*/
#include <stdlib.h>
#include "utils.h"

void enqueue(Queue *q, void *data) { //adauga la finalul cozii
    Node *new_node = malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = NULL;
    if (q->tail) q->tail->next = new_node;
    q->tail = new_node;
    if (!q->head) q->head = new_node;
    q->size++;
}

void enqueue_front(Queue *q, void *data) { //adauga la inceput
    Node *new_node = malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = q->head;
    q->head = new_node;
    if (!q->tail) q->tail = new_node;
    q->size++;
}

void* dequeue(Queue *q) { //primul el
    if (!q->head) return NULL;
    Node *temp = q->head;
    void *data = temp->data;
    q->head = q->head->next;
    if (!q->head) q->tail = NULL;
    q->size--;
    free(temp);
    return data;
}

void push(Stack *s, void *data) { //pune el in stiva
    Node *new_node = malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = s->top;
    s->top = new_node;
}

void* pop(Stack *s) { // scoate ultimul el din stiva
    if (!s->top) return NULL;
    Node *temp = s->top;
    void *data = temp->data;
    s->top = s->top->next;
    free(temp);
    return data;
}

void free_nodes(Node *head) { //elibereaza mem nodurilor
    while(head) {
        Node *t = head;
        head = head->next;
        free(t);
    }
}
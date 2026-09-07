#define _DEFAULT_SOURCE
#include <stdlib.h>
#include <string.h>
#include "incident.h"

Incident* create_incident_list() {
    Incident *sentinel = (Incident*)malloc(sizeof(Incident)); //santinela = incident fictiv
    sentinel->id = 0;
    strcpy(sentinel->priority, "low");
    sentinel->description = (char*)malloc(strlen("test incident") + 1);
    strcpy(sentinel->description, "test incident");
    strcpy(sentinel->status, "solved");
    sentinel->next = sentinel;
    sentinel->prev = sentinel;
    return sentinel;
}

void add_incident_to_list(Incident *sentinel, Incident *new_inc) {
    new_inc->next = sentinel;
    new_inc->prev = sentinel->prev;
    sentinel->prev->next = new_inc;
    sentinel->prev = new_inc;
}

Incident* find_incident_by_id(Incident *sentinel, int id) {
    Incident *curr = sentinel->next;
    while(curr != sentinel) {
        if(curr->id == id) return curr;
        curr = curr->next;
    }
    return NULL;
}
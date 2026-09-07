/* VIERU Ana 324CC*/
#include <stdlib.h>
#include "intervention.h"

Intervention* create_intervention_list() {
    Intervention *s = (Intervention*)malloc(sizeof(Intervention));
    s->incident = NULL;
    s->unit = NULL;
    s->next = s;
    s->prev = s;
    return s;
}

void add_intervention_to_list(Intervention *sentinel, Intervention *new_intv) {
    new_intv->next = sentinel;
    new_intv->prev = sentinel->prev;
    sentinel->prev->next = new_intv;
    sentinel->prev = new_intv;
}
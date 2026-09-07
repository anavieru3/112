/* VIERU Ana 324CC*/
#ifndef INTERVENTION_H
#define INTERVENTION_H

#include "incident.h"

struct unit {
    int id;
    char type;
    int availability;
};

typedef struct intervention {
    Incident *incident;
    struct unit *unit;
    struct intervention *next;
    struct intervention *prev;
} Intervention;

Intervention* create_intervention_list();
void add_intervention_to_list(Intervention *sentinel, Intervention *new_intv);

#endif
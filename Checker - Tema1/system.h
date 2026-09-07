/* VIERU Ana 324CC*/
#ifndef SYSTEM_H
#define SYSTEM_H
#include "incident.h"
#include "intervention.h"
#include "utils.h"

typedef struct system {
    struct unit* units;
    int units_count;
    Incident* incidents;
    Intervention* interventions;
    
    Queue q_high, q_med, q_low, q_avail;
    Stack history;
} System;

System* init_system(int n_units);
void cleanup_system(System *sys);

#endif
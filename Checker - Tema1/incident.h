/* VIERU Ana 324CC*/
#ifndef INCIDENT_H
#define INCIDENT_H

typedef struct incident {
    int id;
    char priority[7];
    char *description;
    char status[11];
    struct incident *next;
    struct incident *prev;
} Incident;

Incident* create_incident_list();
void add_incident_to_list(Incident *sentinel, Incident *new_inc);
Incident* find_incident_by_id(Incident *sentinel, int id);

#endif
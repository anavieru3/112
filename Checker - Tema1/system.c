/* VIERU Ana 324CC*/
#include <stdlib.h>
#include "system.h"

System* init_system(int n_units) {
    System *sys = (System*)calloc(1, sizeof(System));
    sys->units = (struct unit*)malloc(n_units * sizeof(struct unit));
    sys->units_count = n_units;
    sys->incidents = create_incident_list();
    sys->interventions = create_intervention_list();
    return sys;
}

void cleanup_system(System *sys) {
    Incident *curr_i = sys->incidents->next;
    while(curr_i != sys->incidents) {
        Incident *tmp = curr_i;
        curr_i = curr_i->next;
        free(tmp->description);
        free(tmp);
    }
    free(sys->incidents->description);
    free(sys->incidents);

    Intervention *curr_v = sys->interventions->next;
    while(curr_v != sys->interventions) {
        Intervention *tmp = curr_v;
        curr_v = curr_v->next;
        free(tmp);
    }
    free(sys->interventions);

    free_nodes(sys->q_high.head);
    free_nodes(sys->q_med.head);
    free_nodes(sys->q_low.head);
    free_nodes(sys->q_avail.head);
    while(sys->history.top) pop(&sys->history);

    free(sys->units);
    free(sys);
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "system.h"

int main() {
    FILE *in = fopen("tema1.in", "r");
    FILE *out = fopen("tema1.out", "w");
    if (!in || !out)
        return 1;

    int n_units;
    if(fscanf(in, "%d", &n_units) != 1) 
        return 1;
    System *sys = init_system(n_units);

    for (int i = 0; i < n_units; i++) {
        fscanf(in, "%d %c", &sys->units[i].id, &sys->units[i].type);
        sys->units[i].availability = 1;
        enqueue(&sys->q_avail, &sys->units[i]);
    }

    int n_ops;
    fscanf(in, "%d", &n_ops);
    while (n_ops--) {
        char cmd[50];
        fscanf(in, "%s", cmd);

        if (strcmp(cmd, "ADD_INCIDENT") == 0) {
            Incident *ni = (Incident*)malloc(sizeof(Incident));
            char desc[256];
            fscanf(in, "%d %s \"%[^\"]\"", &ni->id, ni->priority, desc);
            ni->description = (char*)malloc(strlen(desc) + 1);
            strcpy(ni->description, desc);
            strcpy(ni->status, "queued");
            add_incident_to_list(sys->incidents, ni); //adaugare incident in lista circulara
            if (strcmp(ni->priority, "high") == 0) 
                enqueue(&sys->q_high, ni);
            else if (strcmp(ni->priority, "medium") == 0) 
                enqueue(&sys->q_med, ni);
            else 
                enqueue(&sys->q_low, ni);

        } else if (strcmp(cmd, "CHECK_UNITS_AVAILABILITY") == 0) {
            fprintf(out, "Number of available units: %d\n", sys->q_avail.size);

        } else if (strcmp(cmd, "DISPATCH") == 0) {
            Queue *target = NULL;
            if (sys->q_high.size > 0) {
                target = &sys->q_high;
            } 
            else if (sys->q_med.size > 0) {
                target = &sys->q_med;
            } 
            else if (sys->q_low.size > 0) {
                target = &sys->q_low;
            }
            if (!target || sys->q_avail.size == 0) {
                fprintf(out, "INVALID OPERATION! ERROR 404\n");
            } else {
                Incident *inc = (Incident*)dequeue(target);
                struct unit *u = (struct unit*)dequeue(&sys->q_avail);
                u->availability = 0;
                strcpy(inc->status, "intervened");
                Intervention *nv = (Intervention*)malloc(sizeof(Intervention));
                nv->incident = inc;
                nv->unit = u;
                add_intervention_to_list(sys->interventions, nv);
                push(&sys->history, nv);
            }

        } else if (strcmp(cmd, "UNDO_LAST_DISPATCH") == 0) {
            Intervention *to_undo = NULL;
            while (sys->history.top) {
                Intervention *curr = (Intervention*)pop(&sys->history);
                if (strcmp(curr->incident->status, "intervened") == 0) {
                    to_undo = curr;
                    break;
                }
            }
            if (!to_undo)
                fprintf(out, "INVALID OPERATION! ERROR 404\n");
            else {
                strcpy(to_undo->incident->status, "queued");
                to_undo->unit->availability = 1;
                enqueue(&sys->q_avail, to_undo->unit);
                Queue *t = (strcmp(to_undo->incident->priority, "high") == 0) ? &sys->q_high : 
                           (strcmp(to_undo->incident->priority, "medium") == 0) ? &sys->q_med : &sys->q_low;
                enqueue_front(t, to_undo->incident);
                to_undo->prev->next = to_undo->next;
                to_undo->next->prev = to_undo->prev;
                free(to_undo);
            }

        } else if (strcmp(cmd, "SOLVED_INCIDENT") == 0) {
            int id; fscanf(in, "%d", &id);
            Incident *inc = find_incident_by_id(sys->incidents, id);
            if (inc && strcmp(inc->status, "intervened") == 0) {
                strcpy(inc->status, "solved");
                Intervention *vi = sys->interventions->next;
                while (vi != sys->interventions) {
                    if (vi->incident == inc) {
                        vi->unit->availability = 1;
                        enqueue(&sys->q_avail, vi->unit);
                        break;
                    }
                    vi = vi->next;
                }
            } else
                fprintf(out, "INVALID OPERATION! ERROR 404\n");

        } else if (strcmp(cmd, "SHOW_UNIT") == 0) {
            int id, f = 0; fscanf(in, "%d", &id);
            for (int i = 0; i < sys->units_count; i++) 
                if (sys->units[i].id == id) {
                    fprintf(out, "Unit %d is type %c and is %s\n", sys->units[i].id, sys->units[i].type, sys->units[i].availability ? "available" : "unavailable");
                    f = 1;
                    break;
                }
            if (!f) 
                fprintf(out, "INVALID OPERATION! ERROR 404\n");

        } else if (strcmp(cmd, "SHOW_INCIDENT") == 0) {
            int id; fscanf(in, "%d", &id);
            Incident *inc = find_incident_by_id(sys->incidents, id);
            if (inc) 
                fprintf(out, "Incident %d has %s priority, the following description: \"%s\" and is %s\n", inc->id, inc->priority, inc->description, inc->status);
            else 
                fprintf(out, "INVALID OPERATION! ERROR 404\n");

        } else if (strcmp(cmd, "SHOW_INTERVENTIONS") == 0) {
            if (sys->interventions->next == sys->interventions)
                fprintf(out, "No intervention has been initiated\n");
            else {
                Intervention *c = sys->interventions->next;
                while (c != sys->interventions) {
                    fprintf(out, "Incident %d was assigned to unit %d, and has the following status: \"%s\"\n", c->incident->id, c->unit->id, c->incident->status);
                    c = c->next;
                }
            }
        }
    }
    cleanup_system(sys);
    fclose(in);
    fclose(out);
    return 0;
}
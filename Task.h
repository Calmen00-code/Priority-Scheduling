#ifndef TASK
#define TASK

#include "header.h"

/* Array of Task to be created */
typedef struct Task {
    int arrival;        /* Arrival time of the task */
    int burst;          /* Burst time of the task */
    int priority;       /* Lower integer indicates higher priority */
    char label[STR];    /* Eg: P1, P2 ... Pn */
    int status;         /* Status of the task in CPU (Eg: Done) */
} Task;

#endif

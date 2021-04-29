/**
 * Program: schedule.c
 * Purpose: Scheduling functions for Priority Preemptive
 * Author : Calmen Chia
 */

#include <stdio.h> /* TODO: Remove this after done debugging */
#include <stdlib.h>
#include "schedule.h"

void process( Task *tasks, int task_size )
{
    int flag_time, total_burst_time, i;
    int *task_idx;
    Task *write_task;
    /* Task running_task; */

    /* Allocation of write_task and task_idx */
    task_idx = calloc(sizeof(task_idx), task_size);
    write_task = calloc(sizeof(write_task), task_size * WRITE_TASK_LIMIT);

    total_burst_time = sum_burst(tasks, task_size);
    printf("Total Burst: %d\n", total_burst_time);

    i = 0, flag_time = 0;
    while ( flag_time < total_burst_time ) {
/*
        arrivalTask(flag_time, tasks, task_idx);
        running_task = priority(flag_time, task_idx, tasks);
        CPU(running_task, write_task[i], &flag_time);
*/
        printf("Flag: %d\n", flag_time);
        ++flag_time; /* TODO: debug */
        ++i;
    }
/*
    gantt_chart(write_task);
*/
}

int sum_burst( Task *tasks, int task_size )
{
    int i;
    int sum = 0;
    for ( i = 0; i < task_size; ++i )
        sum += tasks[i].burst;
    return sum;
}

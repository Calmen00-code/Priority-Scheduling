/**
 * Program: schedule.c
 * Purpose: Scheduling functions for Priority Preemptive
 * Author : Calmen Chia
 */

#include <stdio.h> /* TODO: Remove this after done debugging */
#include <string.h> /* To use memset */
#include <stdlib.h>
#include "schedule.h"

void display( int *arr, int size )
{
    int i;
    for ( i = 0; i < size; ++i )
        printf("%d ", arr[i]);
    printf("\n");
}

/**
 * Main function to run the scheduling PP Algorithm
 */
void process( Task *tasks, int task_size )
{
    int flag_time, total_burst_time, i;
    int *task_idx;
    Task *wrt_task;
    /* Task running_task; */

    /* Allocation of wrt_task and task_idx */
    task_idx = calloc(sizeof(task_idx), task_size);
    wrt_task = calloc(sizeof(wrt_task), task_size * WRITE_TASK_LIMIT);

    total_burst_time = sum_burst(tasks, task_size);

    i = 0, flag_time = 0;
    while ( flag_time < total_burst_time ) {
        /* Mark all elements in task_idx as empty (-1) */
        set_arr(task_idx, task_size, EMPTY_IDX);
        arrival_task(flag_time, tasks, task_size, task_idx);
        /* display( task_idx, task_size ); FIXME: Testing will be done after CPU is done */
        running_task = priority(flag_time, task_idx, tasks);
        printf("Running: %s\n", running_task->label);
/*
        CPU(running_task, wrt_task[i], &flag_time);
*/
        ++flag_time; /* TODO: debug (Should be removed after testing priority function */
        ++i;
    }
/*
    gantt_chart(wrt_task);
*/
    free(task_idx); task_idx = NULL;
    free(wrt_task); wrt_task = NULL;
}

/* Set all element in arr to val */
void set_arr( int *arr, int size, int val )
{
    int i;
    for ( i = 0; i < size; ++i )
        arr[i] = val;
}

/**
 * Find the task that arrives at flag_time and 
 * store the index of the task into task_idx
 */
void arrival_task( int flag_time, Task *tasks, int task_size, int *task_idx )
{
    int i, j;
    j = 0;

    /* Iterate and look for task[i] with burst_time equals to flag_time */
    /* If found, store the index into the task_idx[j] */
    for ( i = 0; i < task_size; ++i ) {
        if ( tasks[i].burst == flag_time ) {
            task_idx[j] = i;
            ++j;    /* Store the next task_idx */
        }
    }
}

/* @return sum of the burst time of tasks */
int sum_burst( Task *tasks, int task_size )
{
    int i;
    int sum = 0;
    for ( i = 0; i < task_size; ++i )
        sum += tasks[i].burst;
    return sum;
}

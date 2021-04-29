/**
 * Program: schedule.c
 * Purpose: Scheduling functions for Priority Preemptive
 * Author : Calmen Chia
 */

#include <stdio.h> /* TODO: Remove this after done debugging */
#include <string.h>     /* To use memset */
#include <stdlib.h>
#include "schedule.h"
#include "file.h"       /* To use DONE and NOT_DONE */

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
    Task running_task;

    /* Allocation of wrt_task and task_idx */
    task_idx = calloc(sizeof(task_idx), task_size);
    wrt_task = calloc(sizeof(wrt_task), task_size * WRITE_TASK_LIMIT);

    total_burst_time = sum_burst(tasks, task_size);

    i = 0, flag_time = 0;
    while ( flag_time < total_burst_time ) {
        /* Mark all elements in task_idx as empty (-1) */
        set_arr(task_idx, task_size, EMPTY_IDX);
        running_task = priority(flag_time, task_idx, tasks, task_size); 
        printf("Running: %s\n", running_task->label);
/*
        CPU(running_task, wrt_task[i], &flag_time);
        display( task_idx, task_size ); FIXME: Testing will be done after CPU is done
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

/**
 * Import : flag_time -> time from 0 up until the latest/current runtime
 *          tasks     -> decide which specific tasks[i] to be returned
 *
 * Purpoose: Return the highest priority task for all the tasks starting from 0 to flag_time
 */
Task* priority( int flag_time, Task *tasks, int task_size )
{
    int i, j, k, pr;
    int pr_idx;         /* Highest priority index for undone task */
    int *undone_idx;    /* Indexes for all undone tasks */
    Task *ret_task;

    /* Setup the undone_idx */
    undone_idx = calloc(sizeof(int), task_size);
    set_arr(undone_idx, task_size, EMPTY_IDX);

    /**                                                 
     * Stops when current arrival time for tasks[i] is
     * greater than current latest time (flag_time)  
     *
     * Store the index of all undone tasks
     */
    i = 0; j = 0;
    while ( i < task_size && tasks[i].arrival < flag_time ) {
        if ( tasks[i].status == NOT_DONE ) {
            undone_idx[j] = i;
            ++j;
        }
        ++i;
    }

    /* Get the first undone priority */
    pr_idx = undone_idx[0];
    pr = tasks[pr_idx].priority;

    /* Find the highest priority among all undone task entries */
    for ( k = 1; k < task_size; ++k ) {
        if ( undone_idx[k] != EMPTY_IDX ) {
            /* Update the latest index with highest priority */
            if ( tasks[k].priority > pr ) {
                pr_idx = k;
                pr = tasks[k].priority;
            }
        }
    }
    ret_task = &tasks[pr_idx];
    free(undone_idx); undone_idx = NULL;
    return ret_task;
}

/**
 * Find the task that arrives at current time (flag_time) and 
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

/* Set all element in arr to val */
void set_arr( int *arr, int size, int val )
{
    int i;
    for ( i = 0; i < size; ++i )
        arr[i] = val;
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

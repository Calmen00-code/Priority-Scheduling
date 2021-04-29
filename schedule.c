/**
 * Program: schedule.c
 * Purpose: Scheduling functions for Priority Preemptive
 * Author : Calmen Chia
 */

#include <stdio.h> /* TODO: Remove this after done debugging */
#include <string.h> 
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
    WriteTask *wrt_task;
    Task *running_task;

    /* Allocation of wrt_task and task_idx */
    task_idx = calloc(sizeof(task_idx), task_size);
    wrt_task = calloc(sizeof(wrt_task), task_size * WRITE_TASK_LIMIT);

    total_burst_time = sum_burst(tasks, task_size);

    i = 0, flag_time = 0;
    while ( flag_time < total_burst_time ) {
        /* Mark all elements in task_idx as empty (-1) */
        set_arr(task_idx, task_size, EMPTY_IDX);
        running_task = priority(flag_time, tasks, task_size); 
        CPU(tasks, task_size, running_task, wrt_task[i], &flag_time);
/*
        display( task_idx, task_size ); FIXME: Testing will be done after CPU is done
*/
        ++i;
    }
/*
    gantt_chart(wrt_task);
*/
    free(task_idx); task_idx = NULL;
    free(wrt_task); wrt_task = NULL;
}

/**
 * Import: tasks        -> For the use of getting next preempt information
 *         running_task -> Decrement on the burst time of current running task
 *         wrt_task     -> Write the process with its remaining burst time
 *         *flag_time   -> Update the flag_time in process function 
 *                      -> Store its final value into wrt_task[i]
 *
 * Purpose: Performs burst_time decrement on the running_task
 */
void CPU( Task *tasks, int task_size, Task *running_task, 
          WriteTask wrt_task, int *flag_time )
{
    int preempt, preempt_idx;
    int stop = FALSE;

    preempt = next_preempt(tasks, task_size, running_task, &preempt_idx);

    /**
     * Stops when higher priority task had preempted OR
     * when current task done execution
     */
    while ( stop == FALSE && running_task->burst > 0 ) {
        running_task->burst--;
        /* Update flag_time in process function (its caller) */
        *flag_time = *flag_time + 1; 

        /* Check if the newly arrived process will preempt current process */
        if ( *flag_time == preempt && 
             isPreempt(tasks, preempt_idx, running_task) == TRUE ) {
            stop = TRUE;
        }
    }

    /* Writing to the wrt_task */
    strcpy(wrt_task.label, running_task->label);
    wrt_task.burst = *flag_time;

    /* Mark the status to be done if the running_task 
       had never got preempted */
    if ( running_task->burst == 0 )
        running_task->status = DONE;
}

/**
 * Compare the priority of the newly arrived process and 
 * return TRUE if newly arrived process had higher priority
 */
int isPreempt( Task *tasks, int preempt_idx, Task *running_task )
{
    int next_priority, curr_priority;
    int preempt = FALSE;

    next_priority = tasks[preempt_idx].priority;
    curr_priority = running_task->priority;

    /* Lower values indicate higher priority. */
    /* Higher priority means Preemption is granted */
    if ( next_priority < curr_priority )
        preempt = TRUE;
    return preempt;
}

/* Returns the next preempt time from current running task */
int next_preempt( Task *tasks, int task_size, 
                  Task *running_task, int *preempt_idx )
{
    int i, j;
    int time;

    /**
     * Find the entries that stores running_task in tasks
     *
     * Using the comparison of address in each entries of task[i]
     * with the address of running_task 
     */
    i = 0;
    while ( &tasks[i] != running_task ) {
        ++i;
    }
    if ( &tasks[i] == running_task ) 
        printf("Same\n");
    else
        printf("%p, %p\n", (void*)&tasks[i], (void*)running_task);

    /* TODO: Test by printing running_task and tasks[i] check if they have the same struct details */
/*
    printf("Task[%d]\n", i);
    printf("Label: %s\n", tasks[i].label);
    printf("Arrival: %d\n", tasks[i].arrival);
    printf("Burst: %d\n", tasks[i].burst);
    printf("Priority: %d\n", tasks[i].priority);
    printf("Status: %d\n", tasks[i].status);
    printf("\n");
    printf("Running Task\n");
    printf("Label: %s\n", running_task->label);
    printf("Arrival: %d\n", running_task->arrival);
    printf("Burst: %d\n", running_task->burst);
    printf("Priority: %d\n", running_task->priority);
    printf("Status: %d\n", running_task->status);
*/
    
    /* ASSERTION: task[i].arrival > running_task->arrival */
    /* Stops when next arrival time was found */
    j = i + 1;
    while ( tasks[j].arrival == running_task->arrival )
        ++j;

    /* Return Next Preempt Index and Next Preempt Time */
    *preempt_idx = j;
    time = tasks[j].arrival;

    return time;
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
            /* Update the latest index with highest priority (lower value) */
            if ( tasks[k].priority < pr ) {
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

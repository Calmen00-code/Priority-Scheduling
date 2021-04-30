/**
 * Program: schedule.c
 * Purpose: Scheduling functions for Priority Preemptive
 * Author : Calmen Chia
 */

#include <stdio.h>  
#include <string.h> 
#include <stdlib.h>
#include "schedule.h"

/**
 * Main function to run the scheduling PP Algorithm
 */
void process( Task *tasks, int task_size )
{
    int flag_time, total_burst_time, i, ii, wrt_size, start_time;
    double ave_turnaround, ave_wait;
    Task *running_task;
    WriteTask *wrt_task;

    /* Allocation of wrt_task */
    wrt_size = task_size * WRITE_TASK_LIMIT;
    wrt_task = malloc(sizeof(WriteTask) * wrt_size);
    for ( ii = 0; ii < wrt_size; ++ii ) {
        wrt_task[ii].turnaround = 0;
        strcpy(wrt_task[ii].label, "");
        wrt_task[ii].status = UNWRITTEN;
    }

    total_burst_time = sum_burst(tasks, task_size);

    /* Check if the first tasks did not start from 0 (Eg: 1,2,3...n) */
    /* If first task did not start from 0, increment the flag_time */
    flag_time = 0;
    if ( tasks[0].arrival > 0 ) {
        flag_time = tasks[0].arrival;
        /* The start time for wrt_task will be arrival time for first task */
        start_time = flag_time;  
    } else  /* Otherwise, the task is start at time 0 */
        start_time = 0;

    i = 0;
    while ( flag_time < total_burst_time ) {
        running_task = priority(flag_time, tasks, task_size); 
        CPU(tasks, task_size, running_task, &wrt_task[i], &flag_time);
        ++i;
    }
    gantt_chart(wrt_task, wrt_size, start_time);
    printf("\n");
    ave_turnaround = ave_turnaround_time(wrt_task, wrt_size);
    ave_wait = ave_wait_time(wrt_task, wrt_size);
    printf("Average Turnaround Time: %.2f\n", ave_turnaround);
    printf("Average Waiting Time: %.2f\n", ave_wait);
    free(wrt_task); wrt_task = NULL;
}

/**
 * Return the average waiting time of the processes 
 */
double ave_wait_time( WriteTask *wrt_task, int wrt_size )
{
    int i, actual_size, wait_time;
    double ave, sum;

    /**                                                     **
     *         CALCULATE SUM OF WAITING TIME                 *
     *  The previous process's turnaround time is the        *
     *  time when current process get execute in CPU         *
     *                                                       *
     *  waiting time = previous process turnaround time -    *
     *                 current arrival time                  *
     *                                                       *
     *  i = 1 as First Process always has 0 waiting time     *
     **                                                     **/
    sum = 0.0;
    for ( i = 1; i < wrt_size - 1; ++i ) {
        /* Waiting Time = Previous Turnaround Time - Current Arrival Time */
        if ( wrt_task[i].status == WRITTEN ) {
            wait_time = wrt_task[i-1].turnaround - wrt_task[i].arrival;
            sum += (double)wait_time;
        }
    }

    actual_size = 0;
    for ( i = 0; i < wrt_size; ++i ) {
        if ( wrt_task[i].status == WRITTEN )
            ++actual_size;
    }
    ave = sum / (double)actual_size;
    return ave;
}

/**
 * Return the average turn around time of the processes 
 */
double ave_turnaround_time( WriteTask *wrt_task, int wrt_size )
{
    int i, actual_size;
    double ave, sum;

    sum = 0.0;
    for ( i = 0; i < wrt_size; ++i )
        sum += wrt_task[i].turnaround - wrt_task[i].arrival;

    actual_size = 0;
    for ( i = 0; i < wrt_size; ++i ) {
        if ( wrt_task[i].status == WRITTEN )
            ++actual_size;
    }
    ave = sum / (double)actual_size;
    return ave;
}

/** 
 * Operation to print the gantt chart of the process 
 */
void gantt_chart( WriteTask *wrt_task, int wrt_size, int start_time )
{ 
    int i, j, idx;

    /* Printing the top line of the gantt chart */
    for ( i = 0; i < wrt_size; ++i ) {
        /* The size of wrt_task is set bigger than actual in advance
           Therefore, a status to check if it was WRITTEN is needed */
        if ( wrt_task[i].status == WRITTEN ) {
            /* Printing bottom line based on distance between 
               previous and current burst time */
            if ( i > 0 ) 
                idx = i-1;
            else 
                idx = 0;
            for ( j = wrt_task[idx].turnaround; j < wrt_task[i].turnaround; ++j )
                printf("---");
        }
    }
    printf("\n");

    if ( start_time > 0 )
        printf("  ");
    /* Printing the Process Label */
    for ( i = 0; i < wrt_size; ++i ) {
        /* The size of wrt_task is set bigger than actual in advance
           Therefore, a status to check if it was WRITTEN is needed */
        if ( wrt_task[i].status == WRITTEN ) {
            printf("|%s", wrt_task[i].label);
            /* Printing space based on distance between 
               previous and current burst time */
            if ( i > 0 ) 
                idx = i-1;
            else 
                idx = 0;
            for ( j = wrt_task[idx].turnaround; j < wrt_task[i].turnaround; ++j ) 
                printf(" ");
        }
    }
    printf("|");    /* Closing Bracket for last Process */
    printf("\n");

    /* Printing the bottom line of the gantt chart */
    for ( i = 0; i < wrt_size; ++i ) {
        /* The size of wrt_task is set bigger than actual in advance
           Therefore, a status to check if it was WRITTEN is needed */
        if ( wrt_task[i].status == WRITTEN ) {
            /* Printing bottom line based on distance between 
               previous and current burst time */
            if ( i > 0 ) 
                idx = i-1;
            else 
                idx = 0;
            for ( j = wrt_task[idx].turnaround; j < wrt_task[i].turnaround; ++j )
                printf("---");
        }
    }
    printf("\n");

    if ( start_time > 0 )
        printf("0 ");
    printf("%d", start_time);
    for ( i = 0; i < wrt_size; ++i ) {
        /* The size of wrt_task is set bigger than actual in advance
           Therefore, a status to check if it was WRITTEN is needed */
        if ( wrt_task[i].status == WRITTEN ) {
            /* Printing bottom line based on distance between 
               previous and current burst time */
            if ( i > 0 ) 
                idx = i-1;
            else 
                idx = 0;
            for ( j = wrt_task[idx].turnaround; j < wrt_task[i].turnaround; ++j ) 
                printf(" ");
            printf(" %d ", wrt_task[i].turnaround);
        }
    }
    printf("\n");
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
          WriteTask *wrt_task, int *flag_time )
{
    int preempt, preempt_idx, *preempt_ptr;
    int stop = FALSE;

    preempt_idx = 0;
    preempt_ptr = &preempt_idx;
    preempt = next_preempt(tasks, task_size, running_task, preempt_ptr);

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
    strcpy(wrt_task->label, running_task->label);
    wrt_task->arrival = running_task->arrival;
    wrt_task->turnaround = *flag_time;
    wrt_task->status = WRITTEN; 
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

/**
 * Inform the next preempt time and index from current running task 
 */
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
    while ( i < task_size && strcmp(tasks[i].label, running_task->label) != 0 )
        ++i;
 
    /* ASSERTION: task[i].arrival > running_task->arrival */
    /* Stops when next arrival time was found */
    j = i;
    while ( j < task_size && tasks[j].arrival == running_task->arrival )
        ++j;

    /* Return Next Preempt Index and Next Preempt Time */
    if ( j < task_size ) {
        *preempt_idx = j;
        time = tasks[j].arrival;
    }
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
    int i, j, k, pr, idx;
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
    while ( i < task_size && tasks[i].arrival <= flag_time ) {
        /* Check if this task had finished execution */
        if ( tasks[i].burst != 0 ) {
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
            /* Compare current priority with the latest highest priority */
            /* Lower Value indicates higher priority */
            idx = undone_idx[k];
            if ( tasks[idx].priority < pr ) {
                pr_idx = idx;               /* Update the latest index */ 
                pr = tasks[idx].priority;   /* Update the latest priority */
            }
        }
    }
    ret_task = &tasks[pr_idx];
    free(undone_idx); undone_idx = NULL;
    return ret_task;
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

/**
 * Program: file.c
 * Purpose: Reading the file that contains Tasks/Processes and store
 *          the task into the Task Array
 * Author : Calmen Chia
 */

#include <stdio.h>
#include <stdlib.h>
#include "header.h" /* To allow the use of DONE and NOT_DONE for Task */
#include "file.h"

/**
 * Read the content of the file and assign all the fields in Task struct
 * This function initialises every fields of the Task Array
 */
Task* read_task( char filename )
{
    FILE *readPtr = NULL;
    Task *task = NULL;
    int i, size;
    int arrival_time, burst_time, priority;

    readPtr = fopen(filename);
    if ( readPtr == NULL )
        perror("Error while reading file");
    else {
        size = read_file_size( filename );  /* Determining the size of the Task Array */
        task = calloc(sizeof(Task), size);

        i = 0;
        while ( fscanf(readPtr, "%d %d %d\n", &arrival_time, 
                       &burst_time, &priority ) != EOF )
        {
            task[i].arrival = arrival_time;
            task[i].burst = burst_time;
            task[i].priority = priority;
            strcpy(task.label, "");
            task[i].status = NOT_DONE;     /* 0 indicates NOT DONE, DONE is assign as 1 */
        }
    }
} 

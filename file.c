/**
 * Program: file.c
 * Purpose: Reading the file that contains Tasks/Processes and store
 *          the task into the Task Array
 * Author : Calmen Chia
 */

#include <stdio.h>
#include <stdlib.h>
#include "file.h"
#include "header.h" /* To allow the use of DONE and NOT_DONE for Task */
                    /* and the use of STR */

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

    readPtr = fopen(filename, "r");
    if ( readPtr == NULL )
        perror("Error while reading file");
    else {
        /* Determining the size of the Task Array */
        size = read_file_size( filename );  
        task = calloc(sizeof(Task), size);

        i = 0;
        while ( fscanf(readPtr, "%d %d %d\n", &arrival_time, 
                       &burst_time, &priority ) != EOF )
        {
            task[i].arrival = arrival_time;
            task[i].burst = burst_time;
            task[i].priority = priority;
            strcpy(task.label, "");
            /* 0 indicates NOT DONE, DONE is assign as 1 */
            task[i].status = NOT_DONE;
        }
        free(readPtr); readPtr = NULL;
    }
    return task;
} 

/**
 * Read the number of lines in a file
 */
int read_file_size( char[] filename )
{
    FILE *readPtr = NULL;
    int line = 0;
    char str[STR];

    readPtr = fopen(filename, "r");
    if ( readPtr == NULL )
        perror("Error while reading file");
    else {
        /* Reading stops when the pointer reaches the end of file */
        while ( fgets( str, STR, readPtr ) != NULL )
            ++line;
        fclose(readPtr); readPtr = NULL;
    }
    return line;
}

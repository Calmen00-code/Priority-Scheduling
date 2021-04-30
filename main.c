/**
 * Program: main.c
 * Purpose: Runs the visualisation of Gant Chart for Priority Scheduling
 * Author : Calmen Chia
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "header.h"
#include "file.h"
#include "Task.h"
#include "sort.h"
#include "schedule.h"

int main()
{
    char fileName[STR] = "";
    Task *tasks = NULL;
    int size;
    int stop = FALSE;

    while ( stop == FALSE ) {
        printf("INPUT: ");
        scanf("%s", fileName);

        if ( strcmp( fileName, "QUIT" ) == 0 )
            stop = TRUE;
        else {
            tasks = read_task(fileName);
            /* tasks is NULL when there is error reading file */
            if ( tasks != NULL ) {
                size = read_file_size(fileName);
                bubble_sort(tasks, size);
                process(tasks, size);
                free(tasks); tasks = NULL;
            }
            printf("\n");
        }
    }
    return 0;
}

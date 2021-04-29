/**
 * Program: main.c
 * Purpose: Runs the visualisation of Gant Chart for Priority Scheduling
 * Author : Calmen Chia
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"
#include "file.h"
#include "Task.h"
#include "sort.h"
#include "schedule.h"

int main(int argc, char*argv[])
{
    char fileName[STR] = "";
    Task *tasks = NULL;
    int size;
    int i;

    if ( argc != 2 ) {
        printf("To run the program,\n");
        printf("Type: ./main.c [filename.txt]\n");
    } else {
        strcpy(fileName, argv[1]);
        tasks = read_task(fileName);
        size = read_file_size(fileName);
        for ( i = 0; i < size; ++i )
            printf("%s: %d %d %d %d\n", tasks[i].label, tasks[i].arrival, tasks[i].burst, tasks[i].priority, tasks[i].status);
        bubble_sort(tasks, size);
        process(tasks, size);
        
        free(tasks); tasks = NULL;
    }
    return 0;
}

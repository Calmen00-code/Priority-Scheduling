#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"
#include "file.h"
#include "Task.h"
#include "sort.h"

int main()
{
    char fileName[STR] = "";
    Task *tasks = NULL;
    int size;
    int i;
/*
    if ( argc != 2 ) {
        printf("To run the program,\n");
        printf("Type: ./main.c [filename.txt]\n");
    } else {
*/
        scanf("%s", fileName);
        /* strcpy(fileName, argv[1]); */
        tasks = read_task(fileName);
        size = read_file_size(fileName);
        printf("Size: %d\n", size); 
        bubble_sort(tasks, size);
        for ( i = 0; i < size; ++i )
            printf("Task %d: %d %d %d %d\n", i, tasks[i].arrival, tasks[i].burst, tasks[i].priority, tasks[i].status);

        free(tasks); tasks = NULL;
/*
    }
*/
    return 0;
}

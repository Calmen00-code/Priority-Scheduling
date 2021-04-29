/**
 * Program: main.c
 * Purpose: Runs the visualisation of Gant Chart for Priority Scheduling
 * Author : Calmen Chia
 */

#include <stdio.h>
#include <string.h>
#include "header.h"
#include "file.h"
#include "Task.h"

int main(int argc, char *argv[])
{
    char fileName[STR] = "";
    Task *tasks = NULL;
    int size = 0;

    if ( argc != 2 ) {
        printf("To run the program,\n");
        printf("Type: ./main.c [filename.txt]\n");
    } else {
        strcpy(fileName, argv[1]);
        tasks = read_task(fileName);
        bubble_sort(task, size);
    }   
    return 0;
}

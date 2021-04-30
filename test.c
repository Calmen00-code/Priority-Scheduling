#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int burst;
    char label[100];
    int status;         /* Initial value is -1 */
} WriteTask;

int main()
{
    int ii;
    WriteTask *wrt_task;
    int wrt_size = 5;

    /* Allocation of wrt_task */
    wrt_task = calloc(sizeof(WriteTask), wrt_size);
    for ( ii = 0; ii < wrt_size; ++ii ) {
        wrt_task[ii].burst = 0;
        strcpy(wrt_task[ii].label, "");
        wrt_task[ii].status = -1;
    }

    for ( ii = 0; ii < wrt_size; ++ii ) {
        printf("Label: %s\n", wrt_task[ii].label);
        printf("Burst: %d\n", wrt_task[ii].burst);
        printf("Status: %d\n", wrt_task[ii].status);
    }
         
    free(wrt_task); wrt_task = NULL;
    return 0;
}

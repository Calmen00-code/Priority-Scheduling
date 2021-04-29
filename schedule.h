#ifndef SCHEDULE
#define SCHEDULE

#include "Task.h"

#define WRITE_TASK_LIMIT 10
#define EMPTY_IDX -1

void process( Task *task, int task_size );
int sum_burst( Task *tasks, int task_size );
void arrival_task( int flag_time, Task *tasks, int task_size, int *task_idx );
void set_arr( int *arr, int size, int val );
Task* priority( int flag_time, Task *tasks, int task_size );
void CPU( Task *running_task, WriteTask wrt_task, int *flag_time );

#endif

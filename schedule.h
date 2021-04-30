#ifndef SCHEDULE
#define SCHEDULE

#include "Task.h"

#define WRITE_TASK_LIMIT 10
#define EMPTY_IDX -1
#define UNWRITTEN 0
#define WRITTEN 1

void process( Task *task, int task_size );
int sum_burst( Task *tasks, int task_size );
void set_arr( int *arr, int size, int val );
Task* priority( int flag_time, Task *tasks, int task_size );
void CPU( Task *tasks, int task_size, Task *running_task, WriteTask *wrt_task, int *flag_time );
int next_preempt( Task *tasks, int task_size, Task *running_task, int *preempt_idx );
int isPreempt( Task *tasks, int preempt_idx, Task *running_task );
void gantt_chart( WriteTask *wrt_task, int wrt_size, int start_time );
double ave_turnaround_time( WriteTask *wrt_task, int wrt_size );
double ave_wait_time( WriteTask *wrt_task, int wrt_size );

#endif

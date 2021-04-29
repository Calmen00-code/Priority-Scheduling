#ifndef SCHEDULE
#define SCHEDULE

#include "Task.h"

#define WRITE_TASK_LIMIT 10

void process( Task *task, int task_size );
int sum_burst( Task *tasks, int task_size );

#endif

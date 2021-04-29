/**
 * Program: sort.c
 * Purpose: Sorts the tasks based on their Arrival Time
 * Author : Calmen Chia
 */

/**
 * Sorts the tasks array according to the arrival times 
 * in ascending order
 */
void bubble_sort( Task *task, int size )
{
    Task *tmp;
    int i, j;
    for ( i = 0; i < size; ++i ) {
        for ( j = 0; j < size; ++j ) {
            if ( task.arrival[j] > task[i].arrival ) {
                tmp = task[j];
                task[j] = task[i];
                task[i] = tmp;
            }
        }
    }
}

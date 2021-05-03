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
    char str[100];
    int i, space;

    space = 5;
    for ( i = 0; i < space; ++i )
        strcat(str, " ");
    printf("%sHello\n", str);
    return 0;
}

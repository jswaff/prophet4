#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "command_internal.h"

#define MAX_INPUT_SZ 256

int command_loop()
{
    int retval = 0;

    char* input = (char*)malloc(MAX_INPUT_SZ);
    if (NULL == input)
    {
        return 1;
    }

    int exit_status;
    do
    {
        fgets(input, MAX_INPUT_SZ, stdin);

        // remove trailing newline
        if ((strlen(input) > 0) && (input[strlen(input) - 1] == '\n'))
        {
            input[strlen(input) - 1] = '\0';
        }

        retval = parse_and_execute(input, &exit_status);

    } while (retval == 0 && exit_status == 0);


    free(input);

    return retval;
}
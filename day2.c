#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 255

#define WINDOWS_NUMBER 4

int main(int argc, char **argv)
{
    // Read input file
    FILE *data = fopen("./data/day2.txt", "r");
    if (data == NULL)
    {
        fprintf(stderr, "Cannot open file\n");
        exit(-1);
    }

    char buffer[BUFFER_SIZE];
    size_t buffer_pos = 0;

    uint horizontal_position, depth, aim = 0;

    while (fread(buffer + buffer_pos, 1, 1, data))
    {
        if (buffer[buffer_pos] == '\n')
        {
            buffer[buffer_pos] = 0;

            char command[50];
            int unit;
            sscanf(buffer, "%s %d", command, &unit);

            if (strcmp(command, "forward") == 0)
            {
                horizontal_position += unit;
                depth += aim * unit;
            }
            else if (strcmp(command, "down") == 0)
            {
                aim += unit;
                // depth += unit;
            }
            else if (strcmp(command, "up") == 0)
            {
                aim -= unit;
                // depth -= unit;
            }
            else
            {
                printf("Command not reconized %s\n", command);
            }

            buffer_pos = 0;
        }
        else
        {
            if (buffer_pos < BUFFER_SIZE)
                buffer_pos++;
            else // Check buffer overflow (if a line is over BUFFER_SIZE characters)
            {
                printf("Buffer overflow \n");
                printf("Buffer content %s \n", buffer);
                return -1;
            }
        }
    }

    printf("x: %d | depth: %d\n", horizontal_position, depth);
    printf("result : %d\n", horizontal_position * depth);

    fclose(data);
}
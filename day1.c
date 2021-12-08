#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 255

#define WINDOWS_NUMBER 4

int main(int argc, char **argv)
{
    // Read input file
    FILE *data = fopen("./data/day1.txt", "r");
    if (data == NULL)
    {
        fprintf(stderr, "Cannot open file\n");
        exit(-1);
    }

    char buffer[BUFFER_SIZE];
    size_t buffer_pos = 0;

    uint value_counter = 0;

    /* PART 1 */
    uint increase_cnt = 0;
    uint previous_value = -1;
    /* PART 1 */

    /* PART 2 */
    uint windowed_increase_cnt = 0;
    uint windowed_sum[WINDOWS_NUMBER] = {0, 0, 0};
    uint windowed_previous_value = -1;
    /* PART 2 */

    while (fread(buffer + buffer_pos, 1, 1, data))
    {
        if (buffer[buffer_pos] == '\n')
        {
            buffer[buffer_pos] = 0;

            uint val = atoi(buffer);
            if (val > previous_value)
                increase_cnt++;

            /* PART 2 */
            for (int i = 0; i < WINDOWS_NUMBER; i++)
            {
                if ((i != (value_counter + 1) % 4) && i <= value_counter)
                    windowed_sum[i] += val;
                else
                {
                    if (windowed_previous_value < windowed_sum[i])
                        windowed_increase_cnt++;
                    windowed_previous_value = windowed_sum[i];
                    windowed_sum[i] = 0;
                }
            }
            /* PART 2 */

            previous_value = val;
            buffer_pos = 0;
            value_counter++;
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

    printf("result : %d\n", increase_cnt);
    printf("result windowed : %d\n", windowed_increase_cnt);

    fclose(data);
}
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>

#define BUFFER_SIZE 14

#define BITS_NB 12

int main(int argc, char **argv)
{
    // Read input file
    FILE *data = fopen("./data/day3.txt", "r");
    if (data == NULL)
    {
        fprintf(stderr, "Cannot open file\n");
        exit(-1);
    }

    char buffer[BUFFER_SIZE];
    buffer[BUFFER_SIZE - 1] = 0;

    uint byte_counter = 0;

    uint bit_recurrence[BITS_NB];

    for (int i = 0; i < BITS_NB; i++)
        bit_recurrence[i] = 0;

    while (fread(buffer, sizeof(*buffer), 13, data) > 0)
    {
        for (int i = 0; i < BITS_NB; i++)
        {
            if (buffer[i] == '1')
                bit_recurrence[i]++;
        }
        byte_counter++;
    }

    uint16_t gamma_rate, epsilon_rate = 0;

    for (int i = 0; i < BITS_NB; i++)
    {
        if (bit_recurrence[i] > (byte_counter / 2))
        {
            gamma_rate |= 1 << (BITS_NB - i - 1);

            printf("%d", 1);
        }
        else
        {
            epsilon_rate |= 1 << (BITS_NB - 1 - i);
            printf("%d", 0);
        }
    }

    printf("\n");

    printf("gamma : %u, epsilon : %u\n", gamma_rate, epsilon_rate);
    printf("result : %d\n", gamma_rate * epsilon_rate);

    fclose(data);
}
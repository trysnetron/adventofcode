#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

const int64_t NUM_ASCII_OFFSET = 48;
const int64_t WHEEL_SIZE = 100;

int main(void)
{
    FILE* file_pointer;
    char* line = NULL;
    size_t file_length;
    ssize_t line_length;

    file_pointer = fopen("./input1.txt", "r");
    if (file_pointer == NULL)
        exit(EXIT_FAILURE);

    int64_t password = 0;
    int64_t wheel = 50;

    while ((line_length = getline(&line, &file_length, file_pointer)) != -1)
    {
        if (line_length < 2)
            continue;

        // Build number
        int64_t number = 0;
        for (size_t i = 1; i < line_length; i++)
        {
            char a = line[i];
            if (a < NUM_ASCII_OFFSET || a > NUM_ASCII_OFFSET + 9)
                break;
            number = number * 10 + ((int64_t)a - NUM_ASCII_OFFSET);
        }

        // Wheel rotation
        switch (line[0])
        {
            case 'L':
            if (wheel == 0)
                password --;
            wheel -= number;
            while (wheel < 0)
            {
                wheel += WHEEL_SIZE;
                password ++;
            }
            if (wheel == 0)
              password ++;
            break;

            case 'R':
            wheel += number;
            while (wheel >= WHEEL_SIZE)
            {
                wheel -= WHEEL_SIZE;
                password ++;
            }
            break;
        }
        // printf("%c%ld \tw%ld \tp%ld\n", line[0], number, wheel, password);
    }

    printf("[dec01 p2] Password: %ld\n", password);

    return 0;
}

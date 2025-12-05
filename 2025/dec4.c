#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

const uint64_t SIZE = 138;

uint8_t get_from_grid(uint8_t *grid, int64_t x, int64_t y)
{
    if (x < 0 || y < 0 || x >= SIZE || y >= SIZE)
        return 0;

    return grid[x + y * SIZE];
}

int64_t delete_on_grid(uint8_t *grid, int64_t x, int64_t y)
{
    uint8_t is_set = get_from_grid(grid, x, y);

    if (is_set)
        grid[x + y * SIZE] = 0;

    return is_set;
}

int64_t part1(uint8_t *grid)
{
    int64_t acc = 0;
    
    for (int64_t x = 0; x < SIZE; x++)
        for (int64_t y = 0; y < SIZE; y++)
        {
            uint8_t g = get_from_grid(grid, x, y);
            if (!g)
                continue;

            int64_t g_neighbours = 0;

            for (int64_t dx = -1; dx <= 1; dx++)
                for (int64_t dy = -1; dy <= 1; dy++)
                {
                    if (dx == 0 && dy == 0)
                        continue;

                    g_neighbours += get_from_grid(grid, x + dx, y + dy);
                }

            if (g_neighbours < 4)
                acc++;
        }

    return acc;
}

int64_t part2(uint8_t *grid)
{
    int64_t acc = 0;
    int64_t was_deleted = 1;
    
    while (was_deleted)
    {
        was_deleted = 0;
    
        for (int64_t x = 0; x < SIZE; x++)
            for (int64_t y = 0; y < SIZE; y++)
            {
                uint8_t g = get_from_grid(grid, x, y);
                if (!g)
                    continue;

                int64_t g_neighbours = 0;

                for (int64_t dx = -1; dx <= 1; dx++)
                    for (int64_t dy = -1; dy <= 1; dy++)
                    {
                        if (dx == 0 && dy == 0)
                            continue;

                        g_neighbours += get_from_grid(grid, x + dx, y + dy);
                    }

                if (g_neighbours < 4)
                {
                    acc++;
                    delete_on_grid(grid, x, y);
                    was_deleted = 1;
                }
            }
    }

    return acc;
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Invalid number of arguments. Should be 1: [file].\n");
        return 1;
    }

    FILE* file_pointer;
    char* line = NULL;
    size_t file_length;

    file_pointer = fopen(argv[1], "r");
    if (file_pointer == NULL)
        exit(1);

    ssize_t line_length;

    uint64_t acc = 0;
    uint64_t line_count = 0;

    uint8_t grid[SIZE * SIZE];

    while ((line_length = getline(&line, &file_length, file_pointer)) != -1)
    {
        assert(line_length - 1 == SIZE);
        

        for (uint64_t i = 0; i < SIZE; i++)
            grid[line_count * SIZE + i] = (line[i] == '@');

        line_count++;
    }

    acc = part2(grid);

    printf("[dec04 p1] Password: %ld\n", acc);

    return 0;
}


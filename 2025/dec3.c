#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

uint64_t tenpow(uint64_t n)
{
    uint64_t a = 1;
    for (uint64_t i = 0; i < n; i++)
        a *= 10;
    return a;
}

uint64_t char_to_int(char c)
{
    assert(c >= '0' && c <= '9');
    return (uint64_t)(c - '0');
}

const uint64_t COUNT = 12;

uint64_t attempt2(char *line, ssize_t line_length)
{
    char c1, c2;
    uint64_t num, max_num;
    max_num = 0;
    uint64_t indexes[COUNT];

    for (uint64_t i = 0; i < COUNT; i++)
        indexes[i] = i;
        
    for (uint64_t ci = 0; ci < COUNT; ci++)
    {
        uint64_t c = COUNT - 1 - ci;
        uint64_t max_c = line_length - 1 - ci;
            
        // printf("working on index %ld\n", c);
        for (; indexes[c] < max_c; indexes[c]++)
        {
            char curr = line[indexes[c]];
            if (curr < '0' || curr > '9')
                continue;
                
            // Calculate number
            num = 0;
            for (uint64_t i = 0; i < COUNT; i++)
                num += char_to_int(line[indexes[i]]) * tenpow(COUNT - 1 - i);

            // printf("\n%ld\n", num);
            if (num > max_num)
                max_num = num;
        }
        indexes[c]--; // Compensate for last increment
    }

    return max_num;
}


uint64_t attempt3(char *line, ssize_t line_length)
{
    assert(line_length < 128);

    uint64_t one_count, num, max_num;
    max_num = 0;
    
    for (unsigned __int128 i = 0; i < 1 << line_length; i++)
    {
        one_count = 0;
        num = 0;
        for (uint64_t j = 0; j < line_length - 1; i++)
        {
            if ((i >> j) & 1 == 0)
                continue;

            one_count++;
            if (one_count > COUNT)
                break;

            num += char_to_int(line[line_length - 2 - j]) * tenpow(COUNT - 1 - one_count);
        }
        if (one_count == COUNT && max_num < num)
            max_num = num;
    }

    return max_num;
}

uint64_t attempt4(char *line, ssize_t line_length)
{
    // c1, c2, c3, c4, c5, c6, c7, c8, c9, c10, c11, c12;
    uint64_t num = 0;
    uint64_t max_num = 0;
    uint64_t p[COUNT], i[COUNT];
    for (uint64_t j = 0; j < COUNT; j++)
        p[j] = tenpow(COUNT - 1 - j);

    for (i[0]  = 0;         i[0] < line_length;  i[0]++)
    for (i[1]  = i[0] + 1;  i[1] < line_length;  i[1]++)
    for (i[2]  = i[1] + 1;  i[2] < line_length;  i[2]++)
    for (i[3]  = i[2] + 1;  i[3] < line_length;  i[3]++)
    for (i[4]  = i[3] + 1;  i[4] < line_length;  i[4]++)
    for (i[5]  = i[4] + 1;  i[5] < line_length;  i[5]++)
    for (i[6]  = i[5] + 1;  i[6] < line_length;  i[6]++)
    for (i[7]  = i[6] + 1;  i[7] < line_length;  i[7]++)
    for (i[8]  = i[7] + 1;  i[8] < line_length;  i[8]++)
    for (i[9]  = i[8] + 1;  i[9] < line_length;  i[9]++)
    for (i[10] = i[9] + 1;  i[10] < line_length; i[10]++)
    for (i[11] = i[10] + 1; i[11] < line_length; i[11]++)
    {
        for (uint64_t j = 0; j < COUNT; j++)
        {
            char c = line[i[j]];

            // printf("%c ", c);    
        
            num += char_to_int(c) * p[j];
        }
        // printf("\n");
        
        if (num > max_num)
            max_num = num;
        num = 0;
    }

    return max_num;
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Invalid number of arguments. Should be 2: [part] [file].\n");
        return 1;
    }

    char part = argv[1][0];

    if (part != '1' && part != '2')
    {
        printf("Invalid part \"%c\"\n", part);
        return 1;
    }
    
    FILE* file_pointer;
    char* line = NULL;
    size_t file_length;

    file_pointer = fopen(argv[2], "r");
    if (file_pointer == NULL)
        exit(1);

    ssize_t line_length;

    uint64_t acc = 0;

    while ((line_length = getline(&line, &file_length, file_pointer)) != -1)
    {
        printf("line length: %ld\n", line_length);
        uint64_t max_num = attempt4(line, line_length - 1);

        printf("max: %ld\n", max_num);
        acc += max_num;
    }

    printf("[dec03 p%c] Password: %ld\n", part, acc);

    return 0;
}


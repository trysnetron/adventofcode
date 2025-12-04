#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

uint64_t upper_bounds[128];
uint64_t lower_bounds[128];
uint64_t bound_count = 0;

uint64_t ten_to_power(uint8_t n)
{
    uint64_t a = 1;
    for (uint8_t i = 0; i < n; i++)
        a *= 10;
    return a;
}

uint64_t repeat(uint64_t base, uint64_t width, uint64_t repetitions)
{
    uint64_t a = base;
    for(uint64_t r = 1; r < repetitions; r++)
        a += base * ten_to_power(r * width);
    return a;
}

uint64_t acc_part1(uint64_t longest_number_length)
{
    uint64_t target = longest_number_length / 2;
    uint64_t acc = 0;
    
    for (uint64_t i = 0; i < target; i++)
    {
        uint64_t from = ten_to_power(i);
        uint64_t to = ten_to_power(i + 1);
        for (uint64_t j = from; j < to; j++)
        {
            uint64_t silly_number = j + j * to;
            for (uint64_t k = 0; k < bound_count; k++)
            {
                if (silly_number < lower_bounds[k] || silly_number > upper_bounds[k])
                    continue;
                printf("found %ld\n", silly_number);
                acc += silly_number;
            }        
        }
    }

    return acc;
} 

uint64_t acc_part2(uint64_t longest_number_length)
{
    uint64_t acc = 0;

    for (uint64_t bound = 0; bound < bound_count; bound++)
    {
        uint64_t upper_bound = upper_bounds[bound];
        uint64_t lower_bound = lower_bounds[bound];
        
        for (uint64_t n = ten_to_power(2); n < ten_to_power(3); n++)
        {
            // 9 (3 * 3)
            uint64_t n3 = n + n * ten_to_power(3) + n * ten_to_power(6);
            if (n3 >= lower_bound && n3 <= upper_bound)
            {
                acc += n3;
                printf("found %ld\n", n3);
            }
        }

        // 1s
        for (uint64_t n = 1; n < 10; n++)
        {
            // 3
            uint64_t nn = n * 111;
            if (nn >= lower_bound && nn <= upper_bound)
            {
                acc += nn;
                printf("found %ld\n", nn);
            }

            // 5
            nn = n * 11111;
            if (nn >= lower_bound && nn <= upper_bound)
            {
                acc += nn;
                printf("found %ld\n", nn);
            }
            
            // 7
            nn = n * 1111111;
            if (nn >= lower_bound && nn <= upper_bound)
            {
                acc += nn;
                printf("found %ld\n", nn);
            }
        }

        // 2s
        for (uint64_t n = 10; n < 100; n++)
        {
            if (n % 11 == 0)
                continue;

            uint64_t a = 0;
            for (uint64_t r = 0; r < 3; r++)
                a += n * ten_to_power(2 * r);
            if (a >= lower_bound && a <= upper_bound)
            {
                acc += a;
                printf("found %ld\n", a);
            }

            a = 0;
            for (uint64_t r = 0; r < 5; r++)
                a += n * ten_to_power(2 * r);
            if (a >= lower_bound && a <= upper_bound)
            {
                acc += a;
                printf("found %ld\n", a);
            }
        }
    }
    
    return acc;
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

    uint64_t number;
    uint64_t longest_number_length = 0;
    uint64_t number_length = 0;
    
    file_pointer = fopen(argv[2], "r");
    if (file_pointer == NULL)
        exit(1);

    // Read only first line
    ssize_t line_length = getline(&line, &file_length, file_pointer);
    if (line_length == -1)
        exit(1);

    // Line reading
    for (uint64_t i = 0; i < line_length; i ++)
    {
        char c = line[i];

        if (c >= '0' && c <= '9')
        {
            number = number * 10 + ((int64_t)(c - '0'));
            number_length++;
        }
        else if (c == '-')
        {
            lower_bounds[bound_count] = number;
            number = 0;
            if (number_length > longest_number_length)
                longest_number_length = number_length;
            number_length = 0;
        }
        if (c == ',')
        {
            upper_bounds[bound_count] = number;
            number = 0;
            if (number_length > longest_number_length)
                longest_number_length = number_length;
            number_length = 0;
            bound_count++;
        }
    }
    upper_bounds[bound_count] = number;
    bound_count++;
    if (number_length > longest_number_length)
        longest_number_length = number_length;

    // Build answer
    //
    printf("Longest number is %ld long.\n", longest_number_length);

    uint64_t acc = acc_part1(longest_number_length);
    
    if (part == '2')
        acc += acc_part2(longest_number_length);

    printf("[dec02 p%c] Password: %ld\n", part, acc);

    return 0;
}

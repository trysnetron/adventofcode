#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Invalid number of arguments. Should be 1: [file].\n");
        exit(1);
    }

    FILE* file_pointer;
    char* line = NULL;
    size_t file_length;
    ssize_t line_length;

    file_pointer = fopen(argv[1], "r");
    if (file_pointer == NULL)
        exit(1);

    const int64_t limit_capacity = 1024;
    int64_t limit_count = 0;
    int64_t limits_lower[limit_capacity];
    int64_t limits_upper[limit_capacity];

    const int64_t item_capacity = 1024;
    int64_t item_count = 0;
    int64_t items[item_capacity];

    int64_t is_parsing_limits = 1;
    // int64_t is_parsing_lower = 1;
    int64_t num_buf;

    while ((line_length = getline(&line, &file_length, file_pointer)) != -1)
    {
        num_buf = 0;
        for (int64_t i = 0; i < line_length; i++)
        {
            char c = line[i];

            if (c >= '0' && c <= '9')
                num_buf = num_buf * 10 + (int64_t)(c - '0');
            else if (c == '-')
            {
                limits_lower[limit_count] = num_buf;
                num_buf = 0;
            }
            else if (c == '\n')
            {
                if (i == 0)
                {
                    is_parsing_limits = 0;
                    continue;
                }
                if (is_parsing_limits)
                    limits_upper[limit_count++] = num_buf;
                else
                    items[item_count++] = num_buf;
            }
            else
            {
                printf("Unexpected character '%c'\n", c);
                exit(2);
            }
        }
    }

    printf("limit count before merging: %ld\n", limit_count);

    // Merge limits

    int64_t continue_deleting = 1;

    while (continue_deleting)
    {
        continue_deleting = 0;
        for (int64_t i = 0; i < limit_count; ++i)
        {
            int64_t start = limits_lower[i], stop = limits_upper[i], new_start, new_stop;

            for (int64_t j = i + 1; j < limit_count; ++j)
            {
                int64_t o_start = limits_lower[j], o_stop = limits_upper[j], delete_current = 0;
                if (o_start < start && o_stop > stop)
                    delete_current = 1, new_start = o_start, new_stop = o_stop;
                else if (o_start >= start && o_stop <= stop)
                    delete_current = 1, new_start = start, new_stop = stop;
                else if (o_start < start && o_stop >= start)
                    delete_current = 1, new_start = o_start, new_stop = stop;
                else if (o_start <= stop && o_stop > stop)
                    delete_current = 1, new_start = start, new_stop = o_stop;

                if (!delete_current)
                    continue;

                limits_lower[i] = new_start;
                limits_upper[i] = new_stop;

                for (int64_t k = j; k < limit_count - 1; ++k)
                    limits_lower[k] = limits_lower[k + 1], limits_upper[k] = limits_upper[k + 1];
                --limit_count;

                continue_deleting = 1;
            }
            // printf("%ld-%ld  add %ld  sub %ld\n", start, stop, to_add, to_sub);
        }
    }

    printf("limit count after merging: %ld\n", limit_count);

    int64_t acc1 = 0, acc2 = 0;
    for (int64_t i = 0; i < limit_count; ++i)
    {
        printf("%ld - %ld\n", limits_lower[i], limits_upper[i]);
        acc2 += limits_upper[i] - limits_lower[i] + 1;

        for (int64_t j = 0; j < item_count; ++j)
            if (limits_upper[i] >= items[j] && limits_lower[i] <= items[j])
                ++acc1;

    }


    printf("[dec05] p1: %ld  p2: %ld\n", acc1, acc2);

    return 0;
}

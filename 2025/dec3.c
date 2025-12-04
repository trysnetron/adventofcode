#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

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
        char c1, c2;
        uint64_t num, max_num;
        max_num = 0;

        for (uint64_t i = 0; i < line_length; i++)
        {
            c1 = line[i];
            if (c1 < '0' || c1 > '9')
                continue;

            for (uint64_t j = i + 1; j < line_length; j++)
            {
                c2 = line[j];
                if (c2 < '0' || c2 > '9')
                    continue;

                num = (uint64_t)(c1 - '0') * 10 + (uint64_t)(c2 - '0');
                if (num > max_num)
                    max_num = num;
            }
        }
        printf("%ld\n", max_num);
        acc += max_num;
    }

    printf("[dec03 p%c] Password: %ld\n", part, acc);

    return 0;
}


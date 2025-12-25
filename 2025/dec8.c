#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define i64 int64_t

i64 sqdist(i64 list_x[], i64 list_y[], i64 list_z[], i64 i1, i64 i2)
{
    assert(i1 != i2);

    i64 dx = list_x[i2] - list_x[i1];
    i64 dy = list_y[i2] - list_y[i1];
    i64 dz = list_z[i2] - list_z[i1];

    return dx * dx + dy * dy + dz * dz;
}

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

    const i64 box_capacity = 1024;
    i64 box_count = 0;
    i64 box_x[box_capacity];
    i64 box_y[box_capacity];
    i64 box_z[box_capacity];
    i64 box_circuits[box_capacity];

    // PARSE

    i64 num_buf;
    char c;
    i64 parse_step = 0;

    while ((line_length = getline(&line, &file_length, file_pointer)) != -1)
    {
        num_buf = 0;
        for (int64_t i = 0; i < line_length; ++i)
        {
            c = line[i];

            if (c >= '0' && c <= '9')
                num_buf = num_buf * 10 + (int64_t)(c - '0');
            else if (c == ',')
            {
                if (parse_step == 0)
                    box_x[box_count] = num_buf;
                else if (parse_step == 1)
                    box_y[box_count] = num_buf;

                ++parse_step;
                num_buf = 0;
            }
            else if (c == '\n')
            {
                box_z[box_count] = num_buf;
                box_circuits[box_count] = box_count;
                ++box_count;
                parse_step = 0;
            }
            else
            {
                printf("Unexpected character '%c'\n", c);
                exit(2);
            }
        }
    }

    // SORT DISTANCES

    const i64 dist_capacity = 1000;
    i64 dist_count = 0;
    i64 dist_from[dist_capacity];
    i64 dist_to[dist_capacity];
    i64 dist_sq[dist_capacity];

    i64 dist, inserted;
    for (i64 i = 0; i < box_count; ++i)
        for (i64 j = i + 1; j < box_count; ++j)
        {
            dist = sqdist(box_x, box_y, box_z, i, j);
            inserted = 0;

            for (i64 k = 0; k < dist_count; ++k)
            {
                if (dist >= dist_sq[k])
                    continue;
                if (dist_count < dist_capacity)
                    ++dist_count;
                for (i64 l = dist_count - 1; l > k; --l)
                {
                    dist_sq[l] = dist_sq[l - 1];
                    dist_from[l] = dist_from[l - 1];
                    dist_to[l] = dist_to[l - 1];
                }
                dist_from[k] = i;
                dist_to[k] = j;
                dist_sq[k] = dist;
                inserted = 1;
                break;
            }
            if (inserted)
                continue;
            if (dist_count >= dist_capacity)
                continue;
            dist_from[dist_count] = i;
            dist_to[dist_count] = j;
            dist_sq[dist_count++] = dist;
        }

    // CIRCUITS

    i64 to_circuit, from_circuit;
    for (i64 i = 0; i < dist_count; ++i)
    {
        from_circuit = box_circuits[dist_from[i]];
        to_circuit = box_circuits[dist_to[i]];

        if (from_circuit == to_circuit)
            continue;

        for (i64 j = 0; j < box_count; ++j)
            if (box_circuits[j] == to_circuit)
                box_circuits[j] = from_circuit;
    }

    const i64 top_net_capacity = 3;
    i64 top_net_ids[top_net_capacity], top_net_counts[top_net_capacity];
    for (i64 i = 0; i < top_net_capacity; ++i)
        top_net_ids[i] = -1, top_net_counts[i] = 0;

    i64 net_n_count;
    for (i64 circuit_id = 0; circuit_id < box_count; ++circuit_id)
    {
        net_n_count = 0;
        for (i64 i = 0; i < box_count; ++i)
            if (box_circuits[i] == circuit_id)
                ++net_n_count;

        for (i64 top_net_i = 0; top_net_i < top_net_capacity; ++top_net_i)
        {
            if (net_n_count <= top_net_counts[top_net_i])
                continue;

            for (i64 top_net_j = top_net_capacity - 1; top_net_j > top_net_i; --top_net_j)
            {
                top_net_ids[top_net_j] = top_net_ids[top_net_j - 1];
                top_net_counts[top_net_j] = top_net_counts[top_net_j - 1];
            }
            top_net_ids[top_net_i] = circuit_id;
            top_net_counts[top_net_i] = net_n_count;
            break;
        }
    }

    i64 acc = 1;
    for (i64 i = 0; i < top_net_capacity; ++i)
        acc *= top_net_counts[i];

    // DEBUG

    for (int64_t i = 0; i < box_count; ++i)
        printf("x:%ld y:%ld z:%ld circuit %ld\n", box_x[i], box_y[i], box_z[i], box_circuits[i]);

    for (i64 i = 0; i < dist_count; ++i)
        printf("%ld from #%ld(%ld, %ld, %ld) to #%ld(%ld, %ld, %ld)\n", dist_sq[i], dist_from[i], box_x[dist_from[i]], box_y[dist_from[i]], box_z[dist_from[i]], dist_to[i], box_x[dist_to[i]], box_y[dist_to[i]], box_z[dist_to[i]]);

    for (i64 i = 0; i < top_net_capacity; ++i)
        printf("top %ld: %ld x %ld\n", i + 1, top_net_ids[i], top_net_counts[i]);


    printf("[dec08] p1: %ld\n", acc);

    return 0;
}

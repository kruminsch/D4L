/*
** INTERNSHIP, 2020
** Get Next Line
** File description:
** GetLine Function
*/

#include "../include/get_next_line.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int check_new_line(char buffer[])
{
    int i = 0;

    while (i < READ_SIZE || buffer[i] != '\0') {
        if (buffer[i] == '\n')
            return (1);
        i = i + 1;
    }
    return (0);
}

void add_buff(int i, int j, char *buffer)
{
    j = j + 1;
    i = 0;
    while (buffer[j] != '\0') {
        buffer[i] = buffer[j];
        i = i + 1;
        j = j + 1;
    }
    while (i < READ_SIZE) {
        buffer[i] = '\0';
        i = i + 1;
    }
}

void append_plus(char *res, char *buffer, int i)
{
    int j = 0;

    while (buffer[j] != '\n' && buffer[j] != '\0') {
        res[i] = buffer[j];
        i = i + 1;
        j = j + 1;
    }
    res[i] = '\0';
    if (buffer[j] == '\n')
        add_buff(i, j, buffer);
    else
        for (int k = 0; k < (READ_SIZE + 1); k = k + 1)
            buffer[k] = '\0';
}

char *append(char *output, char *buffer)
{
    int i = 0;
    char *res;
    size_t size = 0;

    if (output == NULL)
        size = 0;
    else
        while (*(output + size) != '\0')
            ++size;
    if (NULL == (res = malloc(sizeof(char) * (READ_SIZE + 1 + size))))
        return (NULL);
    if (output != NULL)
        while (output[i] != '\0') {
            res[i] = output[i];
            i = i + 1;
        }
    append_plus(res, buffer, i);
    free(output);
    return (res);
}

char *get_next_line(int fd)
{
    static char buffer[READ_SIZE + 1];
    char *output = NULL;
    int status;

    if (check_new_line(buffer)) {
        output = append(output, buffer);
        return (output);
    }
    output = append(output, buffer);
    while (1) {
        status = read(fd, buffer, READ_SIZE);
        if (status == 0 || status == -1 )
            return (NULL);
        if (status < READ_SIZE || check_new_line(buffer))
            break;
        output = append(output, buffer);
    }
    output = append(output, buffer);
    return (output);
}

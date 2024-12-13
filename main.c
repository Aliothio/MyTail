/**
 * @file main.c
 * @author Logan Rostron (loganplaysrunescape@gmail.com)
 * @brief The main file for my implementation of the linux tail command
 * @version 0.1
 * @date 2024-09-24
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <string.h>
#include "tail.h"



int main(int argc, char *argv[])
{
    if (argc != 2 && argc != 4)
    {
        perror("Incorrect Usage");
        exit(1);
    }

    if (argc == 4)
    {
        if (strcmp(argv[1], "-n") != 0)
        {
            perror("Wrong Option");
            exit(1);
        }
    }

    int fd;

    if (argc == 2)
    {
        fd = open(argv[1], O_RDONLY);
    } else
    {
        fd = open(argv[3], O_RDONLY);
    }

    if (fd == -1)
    {
        perror("opening file");
        exit(1);
    }


    if (argc == 2)
    {
        tail(fd, "10");
    } else
    {
        tail(fd, argv[2]);
    }



    close(fd);

    return 0;
}
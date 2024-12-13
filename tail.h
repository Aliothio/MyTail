/**
 * @file tail.h
 * @author Logan Rostron (loganplaysrunescape@gmail.com)
 * @brief Header for tail.c, my implementation of the linux tail command
 * @version 0.1
 * @date 2024-09-24
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef TAIL_H
#define TAIL_H

#define MAX_SIZE 256

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


/**
 * @brief Handles which read function to use and makes the lines into an int
 * 
 * @param fd The file that will be read from
 * @param lines either the number of lines to be read or the starting line in the file
 */
void tail(int fd, char * lines);

/**
 * @brief Reads and Outputs from the line startLine till the end of the file
 * 
 * @param fd The file to be read
 * @param startLine The line of the file to start reading from
 */
void readFrom(int fd, int startLine);

/**
 * @brief Gets the total line length of the file then calls readFrom starting from numLines from the bottom
 * 
 * @param fd The file to get the line length of
 * @param numLines The number of lines from the bottom to be printed
 */
void readTotal(int fd, int numLines);


#endif
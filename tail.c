/**
 * @file tail.c
 * @author Logan Rostron (loganplaysrunescape@gmail.com)
 * @brief My implementation of the linux tail command for default and the -n option
 * @version 0.1
 * @date 2024-09-24
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "tail.h"


/**
 * @brief Handles which read function to use and makes the lines into an int
 * 
 * @param fd The file that will be read from
 * @param lines either the number of lines to be read or the starting line in the file
 */
void tail(int fd, char * lines)
{
    // Setup up lineNum and call the proper function
    int lineNum = 0;
    if (lines[0] == '+')
    {
        lines[0] = '0'; // so that lineNum doesn't have a + in it
        lineNum = atoi(lines);
        readFrom(fd, lineNum);
    } else
    {
        lineNum = atoi(lines);
        readTotal(fd, lineNum);
    }
}

/**
 * @brief Reads and Outputs from the line startLine till the end of the file
 * 
 * @param fd The file to be read
 * @param startLine The line of the file to start reading from
 */
void readFrom(int fd, int startLine)
{
    // Buffer for input and output
    char buffer[MAX_SIZE];
    // Keep track of what line it currently is so that it can write from the correct line
    int currentLine = 1;
    int i = 0;

    while ((read(fd, &buffer[i], sizeof(char))) > 0)
    {
        // When at a newline
        if (buffer[i] == '\n')
        {
            // If it is the right line to start writing from
            if (currentLine >= startLine)
            {
                // Write to the console the buffer using the count of how many chars were loaded into the buffer
                if (write(1, buffer, sizeof(char)*i) == -1)
                {
                    perror("Writing Output");
                    return;
                }
                if (write(1, "\n", sizeof(char)) == -1)
                {
                    perror("Writing Output");
                    return;
                }
            }
            // Next line and reset i for the starting element of buffer
            currentLine++;
            i = 0;
        } else
        {
            i++;
        }
        
    }
    return;
}


/**
 * @brief Gets the total line length of the file then calls readFrom starting from numLines from the bottom
 * 
 * @param fd The file to get the line length of
 * @param numLines The number of lines from the bottom to be printed
 */
void readTotal(int fd, int numLines)
{
    // Buffer for the input
    char buffer[MAX_SIZE];
    // Keep track of currentLine, also acts as the total number of lines in the file
    int currentLine = 1;
    int i = 0;

    while ((read(fd, &buffer[i], sizeof(char))) > 0)
    {
        if (buffer[i] == '\n')
        {
            currentLine++;
            i = 0;
        } else
        {
            i++;
        }
    }
    lseek(fd, 0, SEEK_SET);
    
    if (currentLine - numLines < 1)
    {
        readFrom(fd, 1); // Write starting from the first line if numLines is more than the total lines in the file
    } else
    {
        readFrom(fd, currentLine - numLines); // Write starting from numLines less than the total lines in the file
    }
    return;
}

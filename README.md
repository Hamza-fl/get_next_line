# get_next_line

## Description

This project implements a function `get_next_line` that reads a line from a file descriptor, one line at a time. The function reads up to a specified buffer size (`BUFFER_SIZE`) from the file descriptor into a static buffer, and returns the next line read from the file descriptor.

## Features and Functionality

*   Reads one line at a time from a file descriptor.
*   Uses a static buffer to store the contents of the file descriptor.
*   Handles multiple file descriptors simultaneously.
*   Handles end-of-file (EOF) correctly.
*   Handles errors gracefully.
*   Defined buffer size via macro.

## Technology Stack

*   C

## Prerequisites

*   A C compiler (e.g., GCC or Clang).
*   A text editor or IDE.

## Installation Instructions

1.  Clone the repository:

    ```bash
    git clone https://github.com/Hamza-fl/get_next_line.git
    cd get_next_line
    ```

2.  Compile the library:

    ```bash
    gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 -c get_next_line.c get_next_line_utils.c
    gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 -c main.c # Example usage
    gcc -o executable get_next_line.o get_next_line_utils.o main.o
    ```

    **Note:** You can adjust `BUFFER_SIZE` during compilation using the `-D` flag.  It is crucial to define `BUFFER_SIZE` during the compilation of both `get_next_line.c` and any file using `get_next_line` (like `main.c`).

## Usage Guide

1.  Include the `get_next_line.h` header file in your C program.

2.  Call the `get_next_line` function with the file descriptor as an argument.

3.  The function will return a pointer to a string containing the next line read from the file descriptor, or `NULL` on error or end-of-file.  The returned string is dynamically allocated and must be freed using `free()` by the user.

**Example:**

```c
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "get_next_line.h"

int main() {
    int fd;
    char *line;

    fd = open("example.txt", O_RDONLY); // Ensure example.txt exists

    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }

    while ((line = get_next_line(fd)) != NULL) {
        printf("%s\n", line);
        free(line);
    }

    close(fd);
    return 0;
}
```

Create a file named `example.txt` (or whatever name you use in `open()`) with some text to test the program.

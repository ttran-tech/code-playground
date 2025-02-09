#ifndef COMMON_H
#define COMMON_H

#define NUMBER_LIST_SIZE 5
#define TRUE 1
#define FALSE 0

// Pipe
#define FIFO_PATH "/tmp/integerpool_fifo"
#define FIFO_PERMISSION 0666

// Request type
#define REQUEST_NUMBER 1
#define RELEASE_NUMBER 2
#define VIEW_NUMBER_LIST 3
#define REFRESH_NUMBER 4
#define EXIT 5

#endif
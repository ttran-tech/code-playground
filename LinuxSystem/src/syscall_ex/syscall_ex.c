/**
 *  Demo to show the write() system call
 *  build: gcc syscall_ex.c -o syscall_ex
 *  run: ./syscall_ex
 * 
 */
#include <unistd.h> // for POSIX operation system API
#include <stdio.h>
#include <string.h>
#define BUFFER_SIZE 100

int main()
{
    ssize_t len; // to store the number of byte written from write() syscall
    size_t msg_len; 
    char msg[] = "Hello, World! This message is written from write() system call\n";
    char buff[BUFFER_SIZE];

    // copy the message to the buffer
    strncpy(buff, msg, sizeof(msg));
    msg_len = strlen(buff);

    int fd = 1; // define file descriptor. 1 = standard output
    len = write(fd, buff, msg_len);

    return 0;
}
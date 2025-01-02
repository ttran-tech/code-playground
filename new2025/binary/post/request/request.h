#ifndef REQUEST_H
#define REQUEST_H
#include <stdio.h>
#include <string.h>
#include <curl/curl.h>

#define RESPONSE_BUFFER_SIZE 1024

size_t write_callback(void *received_data, size_t element_size, size_t byte_received, char *response_buffer);
CURLcode send_GET_request(unsigned char *url, unsigned char *response_buffer);
CURLcode send_POST_request();

#endif
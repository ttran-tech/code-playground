#include <stdio.h>
#include <curl/curl.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

/*
pro.c - Send HTTP POST request to Flask web api
Compile: gcc -o pro_get pro_get.c -lcurl
Run: ./pro_get

*/

// Callback function to handle the response data from the API server
size_t write_callback(void *received_data, size_t element_size, size_t byte_received, char *response_buffer)
{
    size_t total_size_received = element_size * byte_received; // Calculate the size of the received data
    strncat(response_buffer, (char*) received_data, total_size_received); // Append data received to the response buffer
    return total_size_received; // Return number of byte processed
}

int main()
{
    CURL *curl;
    CURLcode response_code;

    const char *SERVER_URL = "https://expert-space-halibut-xr5xw7gp74jcv77r-5000.app.github.dev/payload";
    // const char *SERVER_URL = "http://127.0.0.1:5000/payload1";
    char response_buffer[BUFFER_SIZE] = {0};    // Buffer to store the reponse

    // Create CURL handle. In case of multithread, create one handle for every thread
    fprintf(stdout, "Creating CURL handle...");
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init(); 
    if (curl)
    {
        fprintf(stdout, "OK\n");
        // libcurl - Refer to the web tutorial for more detail: https://curl.se/libcurl/c/libcurl-tutorial.html
        // Set server URL
        curl_easy_setopt(curl, CURLOPT_URL, SERVER_URL);

        // Set write callback function
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);

        // Pass response buffer to callback function
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, response_buffer);

        fprintf(stdout, "Sending request to %s\n", SERVER_URL);
        response_code = curl_easy_perform(curl); // Send HTTP request to Web API
        if (response_code != CURLE_OK)
        {
            fprintf(stderr, "CURL request failed: %s\n", curl_easy_strerror(response_code));
            return -1;
        }
        else
        {
            fprintf(stdout, "Server Reponse: %s\n", response_buffer);
        }

        // Cleanup CURL handle
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();

    return 0;
}
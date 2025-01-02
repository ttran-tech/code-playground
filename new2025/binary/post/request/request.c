#include "request.h"

// Callback function to handle the response data from the API server
size_t write_callback(void *received_data, size_t element_size, size_t byte_received, char *response_buffer)
{
    size_t total_size_received = element_size * byte_received; // Calculate the size of the received data
    strncat(response_buffer, (char*) received_data, total_size_received); // Append data received to the response buffer
    return total_size_received; // Return number of byte processed
}

CURLcode send_GET_request(unsigned char *url, unsigned char *response_buffer)
{
    CURL *curl;
    CURLcode response_code;

    // Create CURL handle. In case of multithread, create one handle for every thread
    printf("Creating CURL handle...");
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init(); 
    if (curl)
    {
        printf("OK\n");
        // libcurl - Refer to the web tutorial for more detail: https://curl.se/libcurl/c/libcurl-tutorial.html
        // Set server URL
        curl_easy_setopt(curl, CURLOPT_URL, url);

        // Set write callback function
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);

        // Pass response buffer to callback function
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, response_buffer);

        printf("Sending request to %s\n", url);
        response_code = curl_easy_perform(curl); // Send HTTP request to Web API

        if (response_code != CURLE_OK)
        {
            fprintf(stderr, "CURL request failed: %s\n", curl_easy_strerror(response_code));
        }
        printf("response_buffer: %s\n", response_buffer);
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
    return response_code;
}
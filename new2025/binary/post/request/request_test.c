#include <stdio.h>
#include "request.h"

int main()
{
    unsigned char *url = "https://expert-space-halibut-xr5xw7gp74jcv77r-5000.app.github.dev/payload";
    unsigned char response_buffer[RESPONSE_BUFFER_SIZE] = {0};
    CURLcode response_code;

    response_code = send_GET_request(url, response_buffer);

    if (response_code == CURLE_OK)
    {
        printf("Reponse Data: %s\n", response_buffer);
    }

    unsigned char post_data[POST_DATA_SIZE] = {0};
    sprintf(post_data, "{\"data\": \"%s\"}", "some data");
    unsigned char *http_header = "Content-Type: application/json";
    response_code = send_POST_request(url, response_buffer, post_data, http_header);
    
    if (response_code == CURLE_OK)
    {
        printf("Server Response: %s\n", response_buffer);
    }
}
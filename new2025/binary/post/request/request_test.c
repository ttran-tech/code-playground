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
}
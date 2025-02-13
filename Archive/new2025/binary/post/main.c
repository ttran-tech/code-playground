#include <stdio.h>
#include <curl/curl.h>
#include <string.h>
#include <unistd.h>
#include <openssl/sha.h>

#include "request/request.h"
#include "crypto/crypto.h"

#define BUFFER_SIZE 1024
#define HASH_LEN 256
#define HOSTNAME_LEN 128
#define BASE64_LEN 128
#define ROUTE_LEN 70

/*
pro.c - Send HTTP POST request to Flask web api
Compile: gcc -o pro_post pro_post.c -lcurl
Run: ./pro_post
*/

void generate_base64hash(unsigned char *base64hash)
{
    // Get PID string
    int current_pid = getpid();
    // Get machine hostname
    char hostname[HOSTNAME_LEN] = {0};
    gethostname(hostname, HOSTNAME_LEN);

    // Create hash factor
    char hash_factor[HASH_LEN] = {0};
    snprintf(hash_factor, HASH_LEN, "%s:%d", hostname, current_pid);
    unsigned char hash[SHA256_DIGEST_LENGTH]; // For storing SHA256 hash
    
    // Generate PID hash
    hash_sha256(hash_factor, hash);

    // Encode the hash to base64
    base64_encode(base64hash, hash, SHA256_DIGEST_LENGTH);
}

int main()
{
    unsigned char base64hash[BASE64_LEN];
    generate_base64hash(base64hash);

    char server[ROUTE_LEN] = "https://expert-space-halibut-xr5xw7gp74jcv77r-5000.app.github.dev/";
    char api_route1[ROUTE_LEN] = "53C82EBA31F6D416F331DE9162EBE997";
    char api_route1_url[ROUTE_LEN*2] = {0};

    printf("test\n");
    sprintf(api_route1_url, "%s%s", server, api_route1);

    printf("api_route1_url: %s\n", api_route1_url);

    // Prepare POST data
    unsigned char response_buffer[RESPONSE_BUFFER_SIZE*2] = {0};
    CURLcode response_code;

    char post_data[POST_DATA_SIZE*2] = {0};
    sprintf(post_data, "{\"%s\": \"%s\"}", api_route1, base64hash);
    char *http_header = "Content-Type: application/json";
    response_code = send_POST_request((unsigned char*)api_route1_url, response_buffer, post_data, http_header);
    if (response_code == CURLE_OK)
    {
        printf("Server Response: %s\n", response_buffer);
    }

    return 0;
}
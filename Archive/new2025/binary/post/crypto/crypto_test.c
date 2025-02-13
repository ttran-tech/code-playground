#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <openssl/sha.h>

#include "crypto.h"

#define HASH_LEN 256
#define HOSTNAME_LEN 128
#define BASE64_LEN 128

int main()
{
    // Get PID string
    int current_pid = getpid();
    
    // Get machine hostname
    char hostname[HOSTNAME_LEN] = {0};
    gethostname(hostname, HOSTNAME_LEN);

    // Create hash factor
    char hash_factor[HASH_LEN] = {0};
    snprintf(hash_factor, HASH_LEN, "%s:%d", hostname, current_pid);

    // char *hash_factor = "Hello World";

    unsigned char hash[SHA256_DIGEST_LENGTH]; // For storing SHA256 hash
    
    // Generate PID hash
    hash_sha256(hash_factor, hash);

    // Encode the hash to base64
    unsigned char encoded_b64_hash[BASE64_LEN];
    base64_encode(encoded_b64_hash, hash, SHA256_DIGEST_LENGTH);
    // base64_encode(encoded_b64_hash, hash_factor, strlen(hash_factor));

    printf("Hash Factor: %s\n", hash_factor);
    printf("Raw: %s\n", hash);
    print_hash(hash);
    printf("Encoded base64: %s\n", encoded_b64_hash); // The encoded base64 will be different since EVP_EncodeBlock encode the raw byte instead of the hex.
    return 0;
}
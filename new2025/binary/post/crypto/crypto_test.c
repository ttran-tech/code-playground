#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <openssl/sha.h>

#include "crypto.h"

#define HASH_LEN 512
#define HOSTNAME_LEN 128

int main()
{
    // Get PID string
    int current_pid = getpid();
    char hash_factor[HASH_LEN] = {0};
    
    // Get machine hostname
    char hostname[HOSTNAME_LEN] = {0};
    gethostname(hostname, HOSTNAME_LEN);

    // Create hash factor
    snprintf(hash_factor, HASH_LEN, "%s:%d", hostname, current_pid);

    unsigned char hash[SHA256_DIGEST_LENGTH]; // For storing SHA256 hash
    
    // Generate PID hash
    hash_sha256(hash_factor, hash);

    // Encode the hash to base64
    unsigned char hash_base64[512];
    base64_encode(hash, SHA256_DIGEST_LENGTH, hash_base64);

    printf("Hash Factor: %s\n", hash_factor);
    print_hash(hash);
    printf("Hash base64: %s\n", hash_base64);
    return 0;
}
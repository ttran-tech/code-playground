#include <string.h>
#include <openssl/sha.h>
#include <openssl/evp.h>

#include "crypto.h"

void hash_sha256(char *input, unsigned char *hash)
{
    SHA256_CTX sha256_ctx;
    SHA256_Init(&sha256_ctx);
    SHA256_Update(&sha256_ctx, input, strlen(input));
    SHA256_Final(hash, &sha256_ctx);
}

void print_hash(unsigned char *hash)
{
    printf("SHA256 hash: ");
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
        printf("%02x", hash[i]);
    }
    printf("\n");
}

void base64_encode(const unsigned char *input, size_t length, unsigned char *base64_output)
{
    int base64_len = EVP_EncodeBlock((unsigned char*) base64_output, input, length);
    base64_output[base64_len] = '\0';
}


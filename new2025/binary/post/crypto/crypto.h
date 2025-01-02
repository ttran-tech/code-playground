#ifndef CRYPTO_H
#define CRYPTO_H

#include <stdio.h>
#define KEY_SIZE 32
#define IV_SIZE 16

void hash_sha256(char *input, unsigned char *hash);
void base64_encode(const unsigned char *input, size_t length, unsigned char *base64_output);
void print_hash(unsigned char *hash);

#endif
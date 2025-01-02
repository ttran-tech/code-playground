#ifndef CRYPTO_H
#define CRYPTO_H

#include <stdio.h>
#define KEY_SIZE 32
#define IV_SIZE 16

void hash_sha256(char *input, unsigned char *hash);
void base64_encode(unsigned char *output, unsigned char *input, size_t input_length);
void print_hash(unsigned char *hash);

#endif
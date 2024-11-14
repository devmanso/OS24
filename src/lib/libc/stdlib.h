#pragma once

#include <stddef.h>

#define RAND_MAX 32767

void free(void *ptr);

void *malloc(size_t size);

int rand(void);

void srand(unsigned int seed);

int exit(int status);

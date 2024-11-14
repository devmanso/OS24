#include "stdlib.h"

#include "k/syscalls.h"

static unsigned long int next = 1;

int rand(void) // RAND_MAX is 32767
{
    next = next * 1103515245 + 12345;
    return (unsigned int)(next/65536) % 32768;
}

void srand(unsigned int seed)
{
    next = seed;
}

int exit(int status)
{
    terminate();
    return status;
}

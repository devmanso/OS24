#pragma once

#include <k/types.h>
#include <stdarg.h>

#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2

#define EOF (-1)

typedef struct FILE_t
{
    // File descriptor
    fd_t _fileno;
} FILE;

// Std streams
extern FILE *stdin;
extern FILE *stdout;
extern FILE *stderr;

int fclose(FILE *f);

int fgetc(FILE *f);

char *fgets(char *s, int n, FILE *f);

FILE *fopen(const char *path, const char *mode);

// See printf for implemented flags
int fprintf(FILE *f, const char *fmt, ...);

int fputc(int c, FILE *stream);

int fputs(const char *s, FILE *f);

size_t fread(void *ptr, size_t size, size_t nmemb, FILE *f);

size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *f);

char *gets(char *s);

int getchar();

#define putc fputc

int putchar(int c);

int puts(const char *s);

// Implemented flags :
// - %%
// - %d
// - %i
// - %u
// - %c
// - %x
// - %X
// - %p
int printf(const char *fmt, ...);

// See printf for implemented flags
// Main printf function
int vfprintf(FILE *f, const char *fmt, va_list args);

// TODO: implment fseek and ftell

int fseek(FILE *f, long offset, int whence);
long ftell(FILE *f);
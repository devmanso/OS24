#include "stdio.h"

#include <k/syscalls.h>
#include <k/types.h>
#include <stddef.h>
#include <string.h>

int getchar()
{
    return fgetc(stdin);
}

char *gets(char *s)
{
    char *oldS = s;
    for (;;)
    {
        int c = fgetc(stdin);

        if (c == EOF)
        {
            *s = '\0';
            return s == oldS ? NULL : oldS;
        }

        *s = (char)c;

        ++s;

        if (c == '\n')
        {
            *s = '\0';

            return oldS;
        }
    }
}

int fgetc(FILE *f)
{
    char c;

    ssize_t result;
    do
    {
        result = read(f->_fileno, &c, 1);

        if (result == -1)
            return EOF;
    } while (result != 1);

    return (int)c;
}

// char *fgets(char *s, int n, FILE *f)
// {
//     // TODO : Check EOF
//     if (n == 0)
//         return s;

//     char *oldS = s;
//     size_t totalRead = 0;
//     do
//     {
//         ssize_t result = read(f->_fileno, s, n - 1 - totalRead);

//         // Error encountered
//         if (result < 0)
//             goto ret;

//         // Test end
//         for (ssize_t i = 0; i < result; ++i)
//         {
//             if (s[i] == '\n')
//             {
//                 totalRead += i + 1;
//                 goto ret;
//             }
//         }

//         totalRead += result;
//         s += result;
//     }
//     while (totalRead < (size_t)(n - 1));

// ret:;
//     oldS[totalRead] = '\0';

//     return oldS;
// }

// char *fgets(char *s, int n, FILE *f)
// {
//     if (n == 0 || s == NULL || f == NULL)
//         return NULL;

//     char *oldS = s;
//     size_t totalRead = 0;

//     while (totalRead < (size_t)(n - 1))
//     {
//         ssize_t result = read(f->_fileno, s, n - 1 - totalRead);

//         // Error encountered or EOF reached
//         if (result <= 0)
//         {
//             if (totalRead == 0)
//                 return NULL; // No characters read, return NULL
//             break; // Stop reading
//         }

//         // Test end
//         for (ssize_t i = 0; i < result; ++i)
//         {
//             if (s[i] == '\n')
//             {
//                 totalRead += i + 1;
//                 s += i + 1;
//                 goto ret;
//             }
//         }

//         totalRead += result;
//         s += result;
//     }

// ret:
//     oldS[totalRead] = '\0';
//     return oldS;
// }

// this fgets actually works
char *fgets(char *s, int n, FILE *f)
{
    if (n == 0 || s == NULL || f == NULL)
        return NULL;

    char *oldS = s;
    int totalRead = 0;
    int ch;

    // Read up to n-1 characters
    while (totalRead < n - 1)
    {
        ch = fgetc(f);
        if (ch == EOF)
        {
            if (totalRead == 0) 
                return NULL; // EOF and no characters read
            break; // EOF but some characters read
        }

        *s++ = (char)ch;
        totalRead++;

        if (ch == '\n')
            break; // Stop reading at newline
    }

    *s = '\0'; // Null-terminate the string
    return oldS;
}






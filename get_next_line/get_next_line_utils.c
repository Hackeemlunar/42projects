
#include "get_next_line.h"

void *ft_realloc(void *ptr, size_t oldSize, size_t newSize)
{
    size_t  copySize;

    if (newSize == 0)
    {
        free(ptr);
        return NULL;
    }
    if (ptr == NULL)
        return malloc(newSize);
    void *newPtr = malloc(newSize);
    if (!newPtr)
        return NULL;
    if (oldSize < newSize)
        copySize = oldSize;
    else
        copySize = newSize;
    ft_memcpy(newPtr, ptr, copySize);
    free(ptr);
    return newPtr;
}

void *ft_memcpy(void *dest, const void *src, size_t n)
{
    unsigned char       *d;
    const unsigned char *s;

    d = dest;
    s = src;
    while (n--)
        *d++ = *s++;
    return dest;
}
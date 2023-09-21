#include "shell.h"

/**
 * _memset - fills memory with a constant byte
 * @s: the pointer to the memory area
 * @b: the byte to fill *s with
 * @n: the amount of bytes to be filled
 * Return: (s) a pointer to the memory area s
 */
void *_memset(void *s, int b, size_t n)
{
    unsigned char *ptr = s;
    while (n-- > 0)
    {
        *ptr = (unsigned char)b;
        ptr++;
    }
    return s;
}

/**
 * ffree - frees a string array
 * @pp: string array to free
 */
void ffree(char **pp)
{
    if (!pp)
        return;

    for (size_t i = 0; pp[i]; i++)
    {
        free(pp[i]);
    }

    free(pp);
}

/**
 * _realloc - reallocates a block of memory
 * @ptr: pointer to previous malloc'ated block
 * @old_size: byte size of previous block
 * @new_size: byte size of new block
 *
 * Return: pointer to the reallocated block
 */
void *_realloc(void *ptr, size_t old_size, size_t new_size)
{
    if (!ptr)
    {
        return malloc(new_size);
    }

    if (new_size == 0)
    {
        free(ptr);
        return NULL;
    }

    if (new_size == old_size)
    {
        return ptr;
    }

    void *new_ptr = malloc(new_size);
    if (!new_ptr)
    {
        return NULL;
    }

    size_t min_size = (old_size < new_size) ? old_size : new_size;
    memcpy(new_ptr, ptr, min_size);
    free(ptr);
    return new_ptr;
}


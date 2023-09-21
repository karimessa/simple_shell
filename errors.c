#include "shell.h"

/**
 * _eputs - prints an input string to stderr
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void _eputs(const char *str)
{
    if (!str)
        return;

    while (*str != '\0')
    {
        _eputchar(*str);
        str++;
    }
}

/**
 * _eputchar - writes the character c to stderr
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _eputchar(char c)
{
    return write(STDERR_FILENO, &c, 1) == 1 ? 1 : -1;
}

/**
 * _putfd - writes the character c to the given file descriptor
 * @c: The character to print
 * @fd: The file descriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putfd(char c, int fd)
{
    return write(fd, &c, 1) == 1 ? 1 : -1;
}

/**
 * _putsfd - prints an input string to the given file descriptor
 * @str: the string to be printed
 * @fd: the file descriptor to write to
 *
 * Return: the number of characters put
 */
int _putsfd(const char *str, int fd)
{
    if (!str)
        return 0;

    int count = 0;
    while (*str != '\0')
    {
        if (_putfd(*str, fd) == 1)
        {
            count++;
            str++;
        }
        else
        {
            return -1;
        }
    }
    return count;
}


#include "shell.h"

/**
 * _erratoi - converts a string to an integer
 * @s: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */
int _erratoi(const char *s)
{
    int i = 0;
    long long result = 0;
    int sign = 1;

    if (*s == '+')
        s++;  /* Skip leading '+' */

    if (*s == '-')
    {
        sign = -1;
        s++;  /* Skip leading '-' */
    }

    for (i = 0; s[i] != '\0'; i++)
    {
        if (s[i] >= '0' && s[i] <= '9')
        {
            result *= 10;
            result += (s[i] - '0');

            if (result > INT_MAX || result < INT_MIN)
                return -1;
        }
        else
        {
            return -1;
        }
    }

    return (int)(result * sign);
}

/**
 * print_error - prints an error message
 * @info: the parameter & return info struct
 * @estr: string containing specified error type
 * Return: Nothing
 */
void print_error(info_t *info, const char *estr)
{
    _eputs(info->fname);
    _eputs(": ");
    print_d(info->line_count, STDERR_FILENO);
    _eputs(": ");
    _eputs(info->argv[0]);
    _eputs(": ");
    _eputs(estr);
}

/**
 * print_d - function prints a decimal (integer) number (base 10)
 * @input: the input
 * @fd: the file descriptor to write to
 * Return: number of characters printed
 */
int print_d(int input, int fd)
{
    int (*__putchar)(char) = (fd == STDERR_FILENO) ? _eputchar : _putchar;
    int count = 0;
    long int num = input;

    if (num < 0)
    {
        __putchar('-');
        count++;
        num = -num;
    }

    if (num == 0)
    {
        __putchar('0');
        count++;
    }
    else
    {
        char buffer[12];  // Enough to hold INT_MIN as a string.
        int index = 0;
        while (num > 0)
        {
            buffer[index++] = '0' + (num % 10);
            num /= 10;
        }

        for (int i = index - 1; i >= 0; i--)
        {
            __putchar(buffer[i]);
            count++;
        }
    }

    return count;
}

/**
 * convert_number - converter function, a clone of itoa
 * @num: number
 * @base: base
 * @flags: argument flags
 * Return: string
 */
char *convert_number(long int num, int base, int flags)
{
    static char buffer[50];
    char *ptr = &buffer[49];
    char sign = 0;
    unsigned long n = num;
    const char *array = (flags & CONVERT_LOWERCASE) ? "0123456789abcdef" : "0123456789ABCDEF";

    if (!(flags & CONVERT_UNSIGNED) && num < 0)
    {
        n = -num;
        sign = '-';
    }

    *ptr = '\0';

    do
    {
        *--ptr = array[n % base];
        n /= base;
    } while (n != 0);

    if (sign)
        *--ptr = sign;

    return ptr;
}

/**
 * remove_comments - function replaces the first instance of '#' with '\0'
 * @buf: address of the string to modify
 * Return: Always 0
 */
void remove_comments(char *buf)
{
    int i;

    for (i = 0; buf[i] != '\0'; i++)
    {
        if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
        {
            buf[i] = '\0';
            break;
        }
    }
}


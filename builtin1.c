#include "shell.h"

/**
 * _myhistory - displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _myhistory(info_t *info)
{
    print_list(info->history);
    return 0;
}

/**
 * unset_alias - unsets an alias by removing it from the alias list.
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(info_t *info, char *str)
{
    char *p;
    int ret;

    p = _strchr(str, '=');
    if (!p)
        return 1;
    
    *p = '\0';
    ret = delete_node_at_index(&(info->alias), get_node_index(info->alias, str));
    *p = '=';

    return ret;
}

/**
 * set_alias - sets or updates an alias in the alias list.
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias(info_t *info, char *str)
{
    char *p;

    p = _strchr(str, '=');
    if (!p)
        return 1;

    *p = '\0';
    unset_alias(info, str);
    *p = '=';
    
    return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - prints an alias string.
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias(list_t *node)
{
    char *p;

    if (node)
    {
        p = _strchr(node->str, '=');
        if (p)
        {
            *p = '\0';
            _printf("%s='%s'\n", node->str, p + 1);
            *p = '=';
            return 0;
        }
    }
    return 1;
}

/**
 * _myalias - mimics the alias builtin (man alias).
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _myalias(info_t *info)
{
    int i;

    if (info->argc == 1)
    {
        list_t *node = info->alias;
        while (node)
        {
            print_alias(node);
            node = node->next;
        }
        return 0;
    }

    for (i = 1; info->argv[i]; i++)
    {
        char *p = _strchr(info->argv[i], '=');
        if (p)
        {
            if (set_alias(info, info->argv[i]) != 0)
            {
                perror("set_alias");
                return 1;
            }
        }
        else
        {
            list_t *alias_node = node_starts_with(info->alias, info->argv[i], '=');
            if (alias_node)
            {
                print_alias(alias_node);
            }
        }
    }

    return 0;
}


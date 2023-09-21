#include "shell.h"

/**
 * add_node - adds a node to the start of the list
 * @head: Address of pointer to head node
 * @str: Str field of the node
 * @num: Node index used by history
 *
 * Return: Pointer to the new head of the list
 */
list_t *add_node(list_t **head, const char *str, int num)
{
    if (!head)
        return (NULL);

    list_t *new_head = malloc(sizeof(list_t));
    if (!new_head)
        return (NULL);

    memset(new_head, 0, sizeof(list_t));
    new_head->num = num;

    if (str)
    {
        new_head->str = strdup(str);
        if (!new_head->str)
        {
            free(new_head);
            return (NULL);
        }
    }

    new_head->next = *head;
    *head = new_head;

    return new_head;
}

/**
 * add_node_end - adds a node to the end of the list
 * @head: Address of pointer to head node
 * @str: Str field of the node
 * @num: Node index used by history
 *
 * Return: Pointer to the new node
 */
list_t *add_node_end(list_t **head, const char *str, int num)
{
    if (!head)
        return (NULL);

    list_t *new_node = malloc(sizeof(list_t));
    if (!new_node)
        return (NULL);

    memset(new_node, 0, sizeof(list_t));
    new_node->num = num;

    if (str)
    {
        new_node->str = strdup(str);
        if (!new_node->str)
        {
            free(new_node);
            return (NULL);
        }
    }

    new_node->next = NULL;

    if (!*head)
    {
        *head = new_node;
    }
    else
    {
        list_t *current = *head;
        while (current->next)
            current = current->next;
        current->next = new_node;
    }

    return new_node;
}

/**
 * print_list_str - prints only the str element of a list_t linked list
 * @h: Pointer to the first node
 *
 * Return: Number of nodes in the list
 */
size_t print_list_str(const list_t *h)
{
    size_t i = 0;

    while (h)
    {
        _puts(h->str ? h->str : "(nil)");
        _puts("\n");
        h = h->next;
        i++;
    }

    return i;
}

/**
 * delete_node_at_index - deletes a node at a given index
 * @head: Address of pointer to the first node
 * @index: Index of the node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int delete_node_at_index(list_t **head, unsigned int index)
{
    if (!head || !*head)
        return 0;

    if (index == 0)
    {
        list_t *node = *head;
        *head = (*head)->next;
        free(node->str);
        free(node);
        return 1;
    }

    list_t *current = *head;
    list_t *previous = NULL;

    for (unsigned int i = 0; current && i < index; i++)
    {
        previous = current;
        current = current->next;
    }

    if (!current)
        return 0;

    previous->next = current->next;
    free(current->str);
    free(current);

    return 1;
}

/**
 * free_list - frees all nodes of a list
 * @head_ptr: Address of pointer to the head node
 *
 * Return: void
 */
void free_list(list_t **head_ptr)
{
    if (!head_ptr || !*head_ptr)
        return;

    list_t *current = *head_ptr;
    while (current)
    {
        list_t *next = current->next;
        free(current->str);
        free(current);
        current = next;
    }

    *head_ptr = NULL;
}


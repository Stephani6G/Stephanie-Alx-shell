#include "shell.h"

/**
 * _myhistory - displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0
 */
int _myhistory(info_t *info)
{
    print_list(info->history);
    return 0;
}

/**
 * unset_alias - unsets an alias.
 * @info: Parameter struct.
 * @str: The alias to unset.
 * Return: Always 0 on success, 1 on error.
 */
int unset_alias(info_t *info, char *str)
{
    char *p;
    int ret;

    p = strchr(str, '=');
    if (!p)
        return 1;
    *p = '\0';
    ret = delete_node_by_value(&(info->alias), str);
    *p = '=';
    return ret;
}

/**
 * set_alias - sets an alias to a string.
 * @info: Parameter struct.
 * @str: The alias to set.
 * Return: Always 0 on success, 1 on error.
 */
int set_alias(info_t *info, char *str)
{
    char *p;

    p = strchr(str, '=');
    if (!p)
        return 1;
    if (!*(p + 1))
        return unset_alias(info, str);

    unset_alias(info, str);
    return (add_node_end(&(info->alias), str, 0) == NULL) ? 0 : 1;
}

/**
 * print_alias - prints an alias string.
 * @node: The alias node.
 * Return: Always 0 on success, 1 on error.
 */
int print_alias(list_t *node)
{
    char *p = NULL;

    if (node)
    {
        p = strchr(node->str, '=');
        for (char *a = node->str; a <= p; a++)
            _putchar(*a);
        _putchar('\'');
        _puts(p + 1);
        _puts("'\n");
        return 0;
    }
    return 1;
}

/**
 * _myalias - mimics the alias builtin (man


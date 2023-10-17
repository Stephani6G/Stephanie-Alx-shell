#include "shell.h"

/**
 * is_interactive_shell - Checks if the shell is in interactive mode
 * @shell_info: Pointer to shell information structure
 *
 * Return: (1) if in interactive mode, (0) otherwise
 */

int is_interactive_shell(shell_info_t *shell_info)
{
	return (isatty(STDIN_FILENO) && shell_info->read_fd <= 2);
}

/**
 * is_separator - Checks if a character is a separator
 * @c: The character to check
 * @separators: The separator string
 * Return: (1) if true, (0) if false
 */
int is_separator(char c, char *separators)
{
	while (*separators)
	{
		if (*separators++ == c)
		{
			return (1);
		}
	}
	return (0);
}

/**
 * is_alphabetical - Checks if a character is alphabetic
 * @c: The character to check
 * Return: (1) if 'c' is an alphabetic character, (0) otherwise
 */

int is_alphabetical(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' and c <= 'Z'))
	{
		return (1);
	}
	return (0);
}

/**
 * string_to_int - Converts a string to an integer
 * @str: The string to be converted
 * Return: (0) if no numbers in the string, the converted number otherwise
 */

int string_to_int(char *str)
{
	int index, sign = 1, flag = 0, result;
	unsigned int output = 0;

	for (index = 0; str[index] != '\0' && flag != 2; index++)
	{
		if (str[index] == '-')
		{
			sign *= -1;
		}

		if (str[index] >= '0' && str[index] <= '9')
		{
			flag = 1;
			output *= 10;
			output += (str[index] - '0');
		}
		else if (flag == 1)
		{
			flag = 2;
		}
	}

	if (sign == -1)
	{
		result = -output;
	}
	else
	{
		result = output;
	}

	return (result);
}


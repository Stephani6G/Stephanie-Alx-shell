#include "shell.h"

/**
<<<<<<< HEAD
 * interactive - Check if the shell is in interactive mode.
 * @info: Pointer to a struct containing information.
 *
 * Returns: 1 if in interactive mode, 0 otherwise.
 */
int interactive(info_t *info) {
    return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - Check if a character is a delimiter.
 * @c: The character to check.
 * @delim: The delimiter string.
 *
 * Returns: 1 if the character is a delimiter, 0 otherwise.
 */
int is_delim(char c, char *delim) {
    while (*delim) {
        if (*delim == c) {
            return 1;
        }
        delim++;
    }
    return 0;
}

/**
 * _isalpha - Check if a character is alphabetic.
 * @c: The character to check.
 *
 * Returns: 1 if c is an alphabetic character, 0 otherwise.
 */
int _isalpha(int c) {
    return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) ? 1 : 0;
}

/**
 * _atoi - Convert a string to an integer.
 * @s: The string to be converted.
 *
 * Returns: 0 if there are no numbers in the string, the converted number otherwise.
 */
int _atoi(char *s) {
    int i, sign = 1, flag = 0, output;
    unsigned int result = 0;

    for (i = 0; s[i] != '\0' && flag != 2; i++) {
        if (s[i] == '-') {
            sign *= -1;
        }

        if (s[i] >= '0' && s[i] <= '9') {
            flag = 1;
            result *= 10;
            result += (s[i] - '0');
        } else if (flag == 1) {
            flag = 2;
        }
    }

    output = (sign == -1) ? -result : result;

    return output;
=======
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
>>>>>>> 065e92566483f28f50676d865f950fadc73ad0b1
}


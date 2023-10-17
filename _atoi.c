#include "shell.h"


/**
 * checkInteractive - checks if shell is in interactive
 * @shell_data: pointer to shell data structure
 *
 * Return: 1 if in interactive mode, 0 otherwise
 */

int checkInteractive(shell_data_t *shell_data)
{
	return (isatty(STDIN_FILENO) && shell_data->read_fd <= 2);
}

/**
 * isSeparator - checks if a character is a separator
 * @character: the character to check
 * @separators: the separator string
 *
 * Return: 1 if true, 0 if false
 */
int isSeparator(char character, char *separators)
{
	while (*separators)
	{
		if (*separators++ == character)
		{
			return 1;
		}
	}
	return 0;
}

/**
 * isAlpha - checks if a character is alphabetic
 * @c: The character to check
 *
 * Return: 1 if 'c' is an alphabetic character, 0 otherwise
 */
int isAlpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
	{
		return 1;
	}
	return 0;
}

/**
 * stringToInt - converts a string to an integer
 * @input: the string to be converted
 *
 * Return: (0) if no numbers in the string, the converted number otherwise
 */
int stringToInt(char *input)
{
	int index, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (index = 0; input[index] != '\0' && flag != 2; index++)
	{
		if (input[index] == '-')
		{
			sign *= -1;
		}

		if (input[index] >= '0' && input[index] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (input[index] - '0');
		}
		else if (flag == 1)
		{
			flag = 2;
		}
	}

	if (sign == -1)
	{
		output = -result;
	}
	else
	{
		output = result;
	}

	return (output);
}


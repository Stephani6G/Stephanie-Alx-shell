#include "shell.h"

/**
 * _strcmp - function thAT compares two strings
 * @s1:String 1 to be compared
 * @s2:String 2 to be compared
 * Return: 0 If similar Otherwise the difference
 */

int _strcmp(char *s1, char *s2)
{
int cmp = 0, i, len1, len2;
len1 = _strlen(s1);
len2 = _strlen(s2);

	if (s1 == NULL || s2 == NULL)
		return (1);
	if (len1 != len2)
		return (1);
	for (i = 0; s1[i]; i++)
	{
		if (s1[i] != s2[i])
		{
			cmp = s1[i] - s2[i];
			break;
		}

		else
			continue;
	}
	return (cmp);
}

/**
 * _isalpha -  function that checks if alphabet
 *@c: Character to check if alphabet
 * Return: 1 If true 0 if false success
 */

int _isalpha(int c)
{
if (((c >= 97) && (c <= 122)) || ((c >= 65) && (c <= 90)))
{
return (1);
}

else
{
return (0);
}
}

/**
 * _itoa -  a function that converts integer To char value
 * @n: Int To Convert to char value
 * Return: pointer to to char
 */

char *_itoa(unsigned int n)
{
	int len = 0, i = 0;
	char *s;

	len = intlen(n);
	s = malloc(len + 1);
	if (!s)
		return (NULL);
	*s = '\0';
	while (n / 10)
	{
		s[i] = (n % 10) + '0';
		n /= 10;
		i++;
	}
	s[i] = (n % 10) + '0';
	array_rev(s, len);
	s[i + 1] = '\0';
	return (s);
}

/**
 *  array_rev -  a function that reverses an array of pointers
 * @arr:Array of pointers to Reverse
 * @len:Length Of Array to reverse
 * Return: Void success always
 */

void array_rev(char *arr, int len)
{
	int i;
	char tmp;

	for (i = 0; i < (len / 2); i++)
	{
		tmp = arr[i];
		arr[i] = arr[(len - 1) - i];
		arr[(len - 1) - i] = tmp;
	}
}

/**
 * intlen - a function that determinesthe length of an Int
 * @num: int to determine
 * Return: Length Of the integer
 */

int intlen(int num)
{
	int len = 0;

	while (num != 0)
	{
		len++;
		num /= 10;
	}
	return (len);
}

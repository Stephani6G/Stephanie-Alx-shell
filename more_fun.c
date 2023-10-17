#include "shell.h"

/**
 * _strcpy - a function that copies Source To final Char
 * @dest:the destination char
 * @src:the source char
 * Return: Copies Of the Char *
 */

char *_strcpy(char *dest, char *src)
{
int i;

i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
dest[i] = '\0';
return (dest);
}

/**
 * _strcat - a function that concetrates Two String
 * @dest:First String (s1)
 * @src:Second String (s2)
 * Return:First String and the Second String Char *
 */

char *_strcat(char *dest, char *src)
{
	char *s = dest;

	while (*dest != '\0')
	{
		dest++;
	}

	while (*src != '\0')
	{
		*dest = *src;
		dest++;
		src++;
	}

	*dest = '\0';
	return (s);
}

/**
 * _strchr -  a function that Locatesthe Charactere In a string
 * @s:String to search in
 * @c:Char To Search For innsting
 * Return:  thePointer To Char*
 */

char *_strchr(char *s, char c)
{

	do		{

		if (*s == c)
			{
			break;
			}
		}	while (*s++);

return (s);
}

/**
 * _strncmp -  function that comparesnumber Of Characters Of Two Strings
 * @s1: string 1 to check
 * @s2: string 2 to check
 * @n: the number of Characters To Compare
 *
 * Return: 1 If failure othherwise 0
 */

int _strncmp(const char *s1, const char *s2, size_t n)
{
	size_t i;

	if (s1 == NULL)
		return (-1);
	for (i = 0; i < n && s2[i]; i++)
	{
		if (s1[i] != s2[i])
		{
			return (1);
		}
	}
	return (0);
}

/**
 * _strdup - function that duplicate a String
 * @str:String to duplicate
 * Return: Duplicate String on success, on failure Null
 */

char *_strdup(char *str)
{
	size_t len, i;
	char *str2;

	len = _strlen(str);
	str2 = malloc(sizeof(char) * (len + 1));
	if (!str2)
	{
		return (NULL);
	}

	for (i = 0; i <= len; i++)
	{
		str2[i] = str[i];
	}

	return (str2);
}

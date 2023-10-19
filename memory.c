#include "shell.h"

/**
 **_realloc -  Reallocates A Memory Block using the  malloc and free
 *@ptr: Pointer to the function
 *@old_size: Previous Size Of the pointer to the function
 *@new_size: New Size Of The Pointer of the function
 *Return: Void Pointer Rellocated Memory success
 */

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *result;

	if (new_size == old_size)
		return (ptr);

	if (new_size == 0 && ptr)
	{
		free(ptr);
		return (NULL);
	}
	result = malloc(new_size);

	if (result == NULL)
		return (NULL);
	if (ptr == NULL)
	{
		fill_an_array(result, '\0', new_size);
		free(ptr);
	}

	else
	{
		_memcpy(result, ptr, old_size);
		free(ptr);
	}
	return (result);


}

/**
 * free_all - Free Array Of Char Pointer
 * @cmd:Array Pointer to the function
 * @line:Char Pointer to the pointer
 * Return: Void success
 */

void free_all(char **cmd, char *line)
{
	free(cmd);
	free(line);
	cmd = NULL;
	line = NULL;
}

/**
 * _memcpy - Copy Byte From Source To destination path
 * @dest: Destination Pointer of the the function
 * @src: Source Pointer of the function
 * @n: Size of byte
 * Return: Void success
 */

char *_memcpy(char *dest, char *src, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
	{
		dest[i] = src[i];
	}

	return (dest);
}

/**
 * fill_an_array - Fill the array by constant byte
 * @a:Void Pointer to the function
 * @el: Int of the function
 * @len:Length of integer
 *Return: Void Pointer success
 */

void *fill_an_array(void *a, int el, unsigned int len)
{
	char *p = a;
	unsigned int i = 0;

	while (i < len)
	{
		*p = el;
		p++;
		i++;
	}

	return (a);
}

/**
 * _calloc -  Allocates Memory Forthe  Array
 * @size: Size of byte
 * Return: Void Pointer success
 */

void *_calloc(unsigned int size)
{
	char *a;
	unsigned int i;

	if (size == 0)
	return (NULL);

	a = malloc(size);
	if (a == NULL)
	return (NULL);

	for (i = 0; i < size; i++)
	{
		a[i] = '\0';
	}

	return (a);
}

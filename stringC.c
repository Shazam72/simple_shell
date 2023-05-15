#include "shell.h"

/**
 * _strchr - search a character in a string
 * @str: string to search in
 * @needle: char to search for
 * Return: pointer to the first occurence else NULL
 */
char *_strchr(char *str, char needle)
{
	int i = 0;

	for (i = 0; str[i]; i++)
	{
		if (str[i] == needle)
			return (&str[i]);
	}
	return (NULL);
}

/**
 * _strcmp - compare two strings
 * @str1: first operand
 * @str2: second operand
 * Return: 0 if strings matches else 1
 */
int _strcmp(char *str1, char *str2)
{
	int i = 0, len = 0;

	if (str1 == NULL || str2 == NULL)
		return (1);
	len = _strlen(str1);
	for (i = 0; i <= len; i++)
		if (str1[i] != str2[i])
			return (1);
	return (0);
}

/**
 * _strcmp_n - compare two strings on n characters
 * @str1: first operand
 * @str2: second operand
 * @n: number of character to compare
 * Return: 0 if strings matches else 1
 */
int _strcmp_n(char *str1, char *str2, unsigned int n)
{
	unsigned int i = 0;

	if (str1 == NULL || str2 == NULL || n == 0)
		return (1);
	for (i = 0; i <= n; i++)
	{
		if (str1[i] != str2[i])
			return (1);
	}
	return (0);
}

/**
 * get_string_arr_length - get a NULL terminated array of strings length
 * @args: array of strings
 * Return: number of elements without NULL at last index else 0
 *	    (even) if array is NULL
 */
unsigned int get_string_arr_length(char **args)
{
	unsigned long int i = 0;

	if (args == NULL)
		return (0);
	for (i = 0; args[i]; i++)
		;
	return (i);
}

#include "shell.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * _strncpy - copy n character of a string to another
 * @dest: destination
 * @src: source string
 * @n: number of words to copy
 * Return: pointer to destination string
 */
char *_strncpy(char *dest, char *src, unsigned int n)
{
	unsigned int i = 0;

	if (dest == NULL || src == NULL)
		return (dest);
	for (; i < n; i++)
		dest[i] = src[i];
	return (dest);
}

StringNode *_strsplit(char *str, char *delim)
{
	StringNode *list = NULL;
	char *tmp_str = NULL, *part = NULL, *tmp;

	if (str == NULL)
		return (NULL);
	if (delim == NULL)
	{
		add_string_node(&list, str);
		return (list);
	}
	tmp_str = malloc(sizeof(*tmp_str) * (strlen(str) + _strlen(delim) + 1));
	if (tmp_str == NULL)
		return (NULL);
	_strcpy(tmp_str, str);
	_strcat(tmp_str, delim);

	tmp = tmp_str;
	do {
		part = _strtok(tmp_str, delim);
		add_string_node(&list, tmp_str);
		tmp_str = part;
	} while (_strstr(part, delim));
	free(tmp);
	return (list);
}

/**
 * _isInt - check if a string is a integer
 * @str: string to check
 * Return: 1 if str is an integer else 0
 */
int _isInt(char *str)
{
	for (; *str; str++)
	{
		if (*str < '0' || *str > '9')
			return (0);
	}
	return (1);
}
/**
 * _pow - get natural power
 * @a: number to raise
 * @b: raiser value
 * Return: raised of a to b
 */
int _pow(int a, int b)
{
	if (a == 0)
		return (0);
	if (b == 0)
		return (1);
	if (b == 1)
		return (a);
	return (a * _pow(a, b - 1));
}

/**
 * _strtoi - convert a string into an integer
 * @str: string to convert
 * Return: integer value of str
 */
int _strtoi(char *str)
{
	int i = 0, res = 0, str_len = 0;

	str_len = _strlen(str);
	for (; str[i]; i++)
		res += (str[i] - '0') * _pow(10, str_len - i - 1);
	return (res);
}

#include "shell.h"

/**
 * _strlen - get string length
 * @str: string
 * Return: string's length without null terminated byte
 */
unsigned int _strlen(char *str)
{
	unsigned int n = 0;

	if (str == NULL)
		return (n);
	for (n = 0; str[n]; n++)
		;
	return (n);
}

/**
 * _strstr - search first occurence of string in another
 * @str: string to search in
 * @neddle: string to search
 * Return: pointer to the first occurence
 */
char *_strstr(char *str, char *neddle)
{
	char *pt = NULL;
	int i = 0, j = 0;

	for (i = 0; str[i]; i++)
	{
		for (j = 0; neddle[j] != '\0'; j++)
		{
			if (str[i] == neddle[j])
			{
				i++;
				continue;
			}
			break;
		}
		if (j == 0)
			continue;
		pt = &str[i - j];
		break;
	}
	return (pt);
}

/**
 * _strtok - tokenize a string
 * @str: string to tokenize
 * @delim: delimiter
 * Return: pointer to the rest of the string else NULL
 */
char *_strtok(char *str, char *delim)
{
	int i = 0, j = 0;

	if (str == NULL || delim == NULL)
		return (NULL);

	for (i = 0; str[i] != '\0'; i++)
	{
		for (j = 0; delim[j] != '\0'; j++)
		{
			if (str[i] == delim[j])
			{
				i++;
				continue;
			}
			break;
		}
		if (j == 0)
			continue;
		str[i - j] = '\0';
		break;
	}
	return (&str[i - j + 1]);
}

/**
 * _strcpy - copy a string to another
 * @dest: destination
 * @src: source string
 * Return: pointer to destination string
 */
char *_strcpy(char *dest, char *src)
{
	int i = 0, src_len = 0;

	if (dest == NULL || src == NULL)
		return (dest);
	src_len = _strlen(src);
	for (; i < src_len; i++)
		dest[i] = src[i];
	dest[src_len] = '\0';
	return (dest);
}

/**
 * _strcat - concatenate 2 strings
 * Description: function that concatenate 2 strings, src on dest, user should
 * allocate the required memory that is strlen(dest) + strlen(src) + 1 himself
 * @dest: destination
 * @src: source
 * Return: pointer to destination
 */
char *_strcat(char *dest, char *src)
{
	int i = 0, src_len = 0, dest_len = 0;

	if (dest == NULL || src == NULL)
		return (NULL);
	dest_len = _strlen(dest);
	src_len = _strlen(src);
	for (; i <= src_len; i++)
	{
		dest[dest_len + i] = src[i];
	}
	return (dest);
}

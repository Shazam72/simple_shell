#include "shell.h"
#include <stdlib.h>
#include "types_defines.h"

/**
 * free_string_array - free a string array
 * @arr: array to free
 */
void free_string_array(char **arr)
{
	int i = 0;

	for (i = 0; arr[i]; i++)
		free(arr[i]);
	free(arr);
}

/**
 * cpy_string_array - free a string array
 * @arr: array to free
 * Return: pointer to newly created array
 */
char **cpy_string_array(char **arr)
{
	int i = 0, j = 0, arr_len = 0;
	char **new_arr = NULL;

	if (arr == NULL)
		return (NULL);

	for (arr_len = 0; arr[arr_len]; arr_len++)
		;
	new_arr = (char **) malloc(sizeof(*new_arr) * (arr_len + 1));
	for (i = 0; arr[i]; i++)
	{
		j = _strlen(arr[i]);
		new_arr[i] = malloc(sizeof(*new_arr[i]) * (j + 1));
		if (new_arr[i] == NULL)
		{
			for (; i >= 0; i--)
				free(new_arr[i]);
			free(new_arr);
			return (NULL);
		}
		_strcpy(new_arr[i], arr[i]);
	}
	new_arr[arr_len] = NULL;
	return (arr);
}

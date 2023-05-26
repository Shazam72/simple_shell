#include "shell.h"
#include <stdio.h>
#include <stdlib.h>


StringNode *get_path_list(void)
{
	StringNode *list = NULL;
	char *path = NULL;

	path = _getenv("PATH");
	path += 5;
	list = _strsplit(path, ":");
	return (list);
}

/**
 * _concat_dir_to_file - helper to concatenate dirpath
 * with filename
 * @dirpath: directory's path
 * @filename: filename
 * Return: pointer to full path else NUll (user is reponsible for
 * freeing allocated memory when full path is returned)
 */
char *_concat_dir_to_file(char *dirpath, char *filename)
{
	char *fullpath = NULL;
	int current_dir_length = 0, fullpath_len = 0;

	if (dirpath == NULL || filename == NULL)
		return (NULL);
	current_dir_length = _strlen(dirpath);
	if (dirpath[current_dir_length - 1] != '/')
		current_dir_length++;
	fullpath_len = _strlen(filename) + current_dir_length + 1;
	fullpath = (char *)malloc(sizeof(char) * fullpath_len);
	if (fullpath == NULL)
		return (NULL);
	_strcpy(fullpath, dirpath);
	if (dirpath[current_dir_length - 1] != '/')
		_strcat(fullpath, "/");
	_strcat(fullpath, filename);
	return (fullpath);
}

/**
 * is_file_in - check if a file is in a specific directory
 * @dir: directory path
 * @filename: filename
 * Return: full path else NULL
 */
char *is_file_in(char *dir, char *filename)
{
	struct stat _st;
	char *fullpath = NULL;
	int filename_len = 0;

	if (filename[0] == '/')
	{
		filename_len = _strlen(filename);
		fullpath = (char *) malloc(sizeof(*filename) * (filename_len + 1));
		_strcpy(fullpath, filename);
	}
	else
		fullpath = _concat_dir_to_file(dir, filename);

	if (fullpath == NULL)
		return (NULL);
	if (stat(fullpath, &_st) == 0)
		return (fullpath);
	free(fullpath);
	return (NULL);
}


/**
 * _which - search a file in all PATH directories
 * @filename: filename
 * Return: 0 if founded, 1 if not
 * (user need to free allocated memory for the full file path returned)
 */
char *_which(char *filename)
{
	char *fullpath = NULL;
	StringNode *list = NULL, *tmp = NULL;

	if (filename == NULL)
		return (NULL);
	list = get_path_list();
	add_string_node(&list, "/");
	add_string_node(&list, ".");
	tmp = list;
	for (; tmp; tmp = tmp->next)
	{
		fullpath = is_file_in(tmp->str, filename);
		if (fullpath != NULL)
		{
			free_list(list);
			return (fullpath);
		}
	}
	free_list(list);
	return (NULL);
}

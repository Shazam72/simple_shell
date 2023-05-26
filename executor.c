#include "shell.h"
#include <stdio.h>
#include <stdlib.h>

#define NOT_FOUND_MSG "not found\n"
#define NOT_FOUND_SIZE 10
#define OPTION_DELIMITER " "

/**
 * print_file_notfound - printf msg when command file not found
 * @filename: filename
 */
void print_file_notfound(char *filename)
{
	_print_error(filename, NULL);
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, NOT_FOUND_MSG, NOT_FOUND_SIZE);
}

/**
 * dup_args - duplicate array of arguments for execution
 * @args: arguments to duplicate
 * Return: pointer to newly created array with replacable first element
 */
char **dup_args(char **args)
{
	char **_args = NULL;
	int i = 0, args_len = 0;

	for (i = 0; args[i]; i++)
		;
	args_len = i;
	_args = (char **) malloc(sizeof(*_args) * (args_len + 1));
	for (i = 1; args[i]; i++)
		_args[i] = args[i];
	_args[args_len] = NULL;

	return (_args);
}

/**
 * exec_from_line - execute command from readed line
 * @readed: readed line
 * @show_errors: show execution errors, any number other than zero to show
 * Return: 0 if no problem appear else -1
 */
int exec_from_line(char *readed, int show_errors)
{
	StringNode *lines = NULL, *line = NULL, *tmp = NULL;
	char **args = NULL;
	int res_exec = 0;

	if (readed == NULL)
		return (-1);
	lines = _strsplit(readed, "\n");
	if (lines == NULL)
		return (-1);
	for (line = lines; line->next; line = line->next)
	{
		tmp = _strsplit(line->str, OPTION_DELIMITER);
		if (tmp == NULL)
			return (-1);

		args = array_from_string_list(tmp);
		res_exec = exec_args(args, show_errors);
		free_string_array(args);
		free_list(tmp);
	}
	free_list(lines);
	return (res_exec);
}

/**
 * _callsys - call system for execution command
 * @args: NULL terminated array of arguments
 * @show_errors: show execution errors, any number other than zero to show
 * Return:
 *	0 if no problem appear
 *	2 if executed command failed
 *	-1 if failed to clone process
 */
int _callsys(char **args, int show_errors)
{
	int status;
	pid_t child;


	child = fork();
	if (child == -1)
	{
		if (show_errors != 0)
			perror("");
		return (-1);
	}
	if (child == 0)
	{
		if (execve(args[0], args, environ) == -1 && show_errors != 0)
			perror(_getenv("EXECUTION_FILENAME") + 19);
		return (2);
	}
	else
		waitpid(child, &status, 0);
	return (0);
}

/**
 * exec_args - execute command from array of arguments
 * @args: NULL terminated array of arguments
 * @show_errors: show execution errors, any number other than zero to show
 * Return:
 *	0 if no problem appear
 *	1 if executed command failed
 *	-1 for any other problem
 */
int exec_args(char **args, int show_errors)
{
	int res_exec = 0;
	char *fullpath = NULL;
	char **_args = NULL;

	res_exec = exec_ops_func(args[0], args);
	if (res_exec != 1)
		return (res_exec);
	res_exec = 0;
	fullpath = _which(args[0]);
	_args = args;
	if (fullpath == NULL)
	{
		print_file_notfound(args[0]);
		return (0);
	}
	else
	{
		_args = dup_args(args);
		_args[0] = (char *) malloc(sizeof(*_args[0]) * (_strlen(fullpath) + 1));
		strcpy(_args[0], fullpath);
	}
	res_exec = _callsys(_args, show_errors);
	free(_args[0]);
	free(_args);
	free(fullpath);
	return (res_exec);
}

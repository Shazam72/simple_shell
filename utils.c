#include "shell.h"

/**
 * _realloc - reallocation memory
 * @ptr: pointer to the momory to reallocate
 * @old_size: previous size of memory
 * @new_size: new size of memory
 * Return: pointer to the new reallocated memory
 */
void *_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void *new_memory = NULL;

	if (new_size == old_size)
		return (ptr);
	if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}
	new_memory = malloc(new_size);
	if (ptr == NULL)
		return (new_memory);
	if (old_size > new_size)
		_memcpy(new_memory, ptr, new_size);
	else
		_memcpy(new_memory, ptr, old_size);

	free(ptr);
	return (new_memory);
}

/**
 * _memcpy - copy bytes from an area to another
 * @dest: destination
 * @src: source
 * @size: number oof bytes to copy
 */
void _memcpy(void *dest, void *src, size_t size)
{
	size_t i = 0;
	char *_c1 = NULL;
	char *_c2 = NULL;

	if (size == 0)
		return;
	_c1 = (char *) dest;
	_c2 = (char *) src;

	for (i = 0; i < size; i++)
		_c1[i] = _c2[i];
}

/**
 * safe_exit - free all env variables before exiting
 * @exit_msg: msg to print on stderr before exiting
 * @exit_code: exit code
 */
void safe_exit(char const *exit_msg, int exit_code)
{
	free_env();
	if (exit_msg != NULL)
		perror(exit_msg);
	exit(exit_code);
}

/**
 * _print_error - printf on stderr
 * @msg: error msg
 * @prefix: prefix to print before error msg: Default: shell name
 */
void _print_error(char *msg, char *prefix)
{
	if (msg == NULL)
		return;
	if (prefix == NULL)
	{
		char *shell_name = NULL;

		shell_name = _getenv("EXECUTION_FILENAME")
			+ _strlen("EXECUTION_FILENAME=");
		write(STDERR_FILENO, shell_name, _strlen(shell_name));
		write(STDERR_FILENO, ": ", 2);
	}
	else
		write(STDERR_FILENO, prefix, _strlen(prefix));
	write(STDERR_FILENO, msg, _strlen(msg));
}

/**
 * exit_interactive - exit interractive mode
 * @args: array of arguments
 * Return: number of printed variables
 */
int exit_interactive(char **args)
{
	if (isatty(STDIN_FILENO))
	{
		if (args == NULL)
			write(STDERR_FILENO, "\nexit\n", 6);
		else
			write(STDERR_FILENO, "exit\n", 5);
	}
	free_env();
	exit(0);
}

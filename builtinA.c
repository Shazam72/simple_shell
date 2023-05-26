#include "shell.h"
#include "types_defines.h"
#include <stdio.h>
#include <unistd.h>

/**
 * set_alias -A function that sets an alias to string variable
 * @data: The struct parameter variable
 * @s: The alias string
 * Return: 0 If successful, else 1 on fail
 */
int set_alias(data_t *data, char *s);

/**
 *unset_alias - A function that removes an alias from a string
 *@s:The string alias
 *@data:My structure parameter
 *Return:0 if successful, else 1 on failuire
 */
int unset_alias(data_t *data, char *s);

/**
 *_alias_display - A function that works as an alias command
 *@data: A Structure storing uniform constant function
 *prototypes holding potential arguments.
 *Return:Always Success (0)
 */
int _alias_display(data_t *data);

/**
 * print_env - printf the current env state
 * @args: array of arguments
 * Return: 0
 */
int print_env(char __attribute__((__unused__)) **args)
{
	int i = 0;
	size_t var_len = 0;

	for (i = 0; environ[i]; i++)
	{
		if (_strcmp(environ[i], _getenv("EXECUTION_FILENAME")) == 0)
			continue;
		var_len = _strlen(environ[i]);
		write(STDOUT_FILENO, environ[i], var_len);
		write(STDOUT_FILENO, "\n", 1);
	}
	return (0);
}

/**
 * exit_bultin - exit builtin command
 * @args: array of arguments
 * Return: EXIT_BUILTIN_STATUS
 */
int exit_bultin(char **args)
{
	unsigned int args_len = 0;

	args_len = get_string_arr_length(args);
	if (args_len == 1 || args_len == 2)
	{
		if (args_len == 2)
		{
			if (_isInt(args[1]))
				_setenv("EXIT_CODE", args[1], 1);
			else
			{
				_setenv("EXIT_CODE", "2", 1);
				_print_error("1: exit: ", NULL);
				_print_error("Illegal number: ", "");
				_print_error(args[1], "");
				_print_error("\n", "");
			}
		}
		else
			_setenv("EXIT_CODE", "0", 1);
		return (EXIT_BUILTIN_STATUS);
	}
	else
		_print_error("exit: too many arguments\n", "");
	return (0);
}

/**
 * _setenv_cmd - builtin setenv command function
 * @args: array of arguments
 * Return: 0 on success else -1
 */
int _setenv_cmd(char **args)
{
	unsigned int args_len = 0;

	args_len = get_string_arr_length(args);
	if (args_len != 3)
	{
		_print_error("Usage: setenv VARIABLE VALUE\n", "");
		return (-1);
	}
	_setenv(args[1], args[2], 1);
	return (0);
}

#include "builtin.h"
#include "shell.h"
#include "types_defines.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * _unsetenv_cmd - builtin command for unsetting env variable
 * @args: array of argument
 * Return: 0 if success else -1
 */
int _unsetenv_cmd(char **args)
{
	unsigned int args_len = 0;
	int res = 0;

	args_len = get_string_arr_length(args);
	if (args_len != 2)
	{
		_print_error("Usage: unsetenv VARIABLE\n", "");
		return (-1);
	}
	res = _unsetenv(args[1]);
	if (res == 1)
		return (-1);
	return (0);
}

/**
 * _cd - builtin for change dir
 * @args: array of argument
 * Return: 0 if success else -1
 */
int _cd(char **args)
{
	int res = 0;

	res = chdir(args[1]);
	if (res == 0)
	{
		_setenv("OLDPWD", _getenv("PWD") + 4, 1);
		_setenv("PWD", args[1], 1);
	}
	if (res == -1)
	{
		_print_error("cd: ", NULL);
		_print_error(args[1], "");
		_print_error(": ", "");
		perror("");
	}
	return (0);
}

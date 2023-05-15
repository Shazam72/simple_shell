#include "builtin.h"
#include "shell.h"
#include "types_defines.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * get_ops_func - get corresponding built_in_func for command_name
 * @command_name: command name
 * Return: corresponding built_in_func else NULL
 */
built_in_func get_ops_func(char *command_name)
{
	Built_in_ops ops[] = {
		{"env", print_env},
		{"exit", exit_bultin},
		{"setenv", _setenv_cmd},
		{"unsetenv", _unsetenv_cmd},
		{"cd", _cd},
		{NULL, NULL}
	};
	int i = 0;

	for (i = 0; ops[i].op_name; i++)
		if (_strcmp(ops[i].op_name, command_name) == 0)
			return (ops[i].func);
	return (NULL);
}

/**
 * exec_ops_func - execution a built function if founded
 * @command_name: command name
 * @args: array of arguments
 * Return: result of built function execution else 1 if
 *	    no built in function matches
 */
int exec_ops_func(char *command_name, char **args)
{
	built_in_func op_func = NULL;
	int res = 0;

	op_func = get_ops_func(command_name);
	if (op_func == NULL)
		return (1);
	res = op_func(args);
	return (res);
}

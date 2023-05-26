#include "builtin.h"
#include "shell.h"
#include "types_defines.h"
#include <stdlib.h>
#include <unistd.h>

/**
 * get_args - get right arguments from command line argv
 * @argv: command line arguments
 * Return: pointar to arguments
 */
char **get_args(char *argv[])
{
	char **args = NULL;
	int i = 0, args_len = 0;

	if (argv == NULL)
		return (NULL);
	for (i = 1; argv[i]; i++)
		;
	args_len = i;
	args = (char **) malloc(sizeof(*args) * args_len);
	if (args == NULL)
		return (NULL);
	for (i = 0; i < args_len; i++)
		args[i] = argv[i + 1];

	return (args);
}

/**
 * main - simple shell program
 * @argc: number command line arguments
 * @argv: command line arguments
 * Return: always 0
 */
int main(int argc, char *argv[])
{
	int res_exec = 0;

	environ = init_env(0);
	_setenv("EXECUTION_FILENAME", argv[0], 1);
	if (argc == 1)
	{
		char *readed = NULL;

		while (readed == NULL)
		{
			read_line(&readed);
			res_exec = exec_from_line(readed, 1);
			free(readed);
			if (!isatty(STDIN_FILENO) || res_exec == EXIT_BUILTIN_STATUS)
			{
				exit(res_exec);
				if (res_exec == EXIT_BUILTIN_STATUS)
				{
					res_exec = _strtoi(_getenv("EXIT_CODE") + 10);
				}
				break;
			}
			readed = NULL;
		}
	}
	else
	{
		char **args = NULL;

		args = get_args(argv);
		if (args == NULL)
			return (-1);
		exec_args(args, 1);
		free(args);

	}
	free_env();
	return (res_exec);
}

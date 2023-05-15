#include "shell.h"

/**
 * read_line - print a prompt line
 * @readed: pointer to where store the readed content
 * Return: number content readed otherwise -1
 */
ssize_t read_line(char **readed)
{
	char *content = NULL;
	size_t n = 1024;
	int len = 0;

	do {
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, PROMPT_SYMBOL, 2);
		len = _getline(&content, &n);
		if (len == -1 || (len == 0 && content == NULL))
			exit_interactive(NULL);
		if (len == 1 && content[0] == '\n')
			content = NULL;
	} while (content == NULL);
	*readed = content;
	return (len);
}



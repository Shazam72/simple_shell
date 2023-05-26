#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * save_buff - save buffed stdin entries
 * @input: pointer to the total readed from entries
 * @_buff: buffer that store part of the stdin entries
 * @input_len: total readed from stdin
 * @res_rd: total readed from buffer
 */
void save_buff(char **input, char **_buff, int *input_len, int *res_rd)
{
	if (*input_len == *res_rd)
	{
		*input = (char *) _realloc(*input, BUFFER_READ_SIZE, *res_rd + 1);
		_strcpy(*input, *_buff);
	}
	else
	{
		int prev_input_len = *input_len - *res_rd + 1;

		*input = (char *) _realloc(*input, prev_input_len, *input_len);
		_strcat(*input + prev_input_len - 1, *_buff);
	}
}

/**
 * init_input - allocate memory for input and buffer stdin
 * @_buff: buffer
 * @input: input
 */
void init_input(char **input, char **_buff)
{
	*input = (char *) malloc(sizeof(**input) * BUFFER_READ_SIZE);
	*_buff = (char *) malloc(sizeof(**_buff) * BUFFER_READ_SIZE);
}

/**
 * free_input - free allocatee memory for input and buffer stdin
 * @_buff: buffer
 * @input: input
 */
void free_input(char **input, char **_buff)
{
	free(*_buff);
	free(*input);
}

/**
 * _getline - read a line from stdin
 * @buff: pointer to buffer where to put readed content
 * @n: pointer to number of readed character
 * Return: number of readed content else -1
 */
ssize_t _getline(char **buff, size_t *n)
{
	char *_buff = NULL, *input = NULL;
	int res_rd = 0, input_len = 0;

	init_input(&input, &_buff);
	if (input == NULL || _buff == NULL)
		return (-1);
	while (1)
	{
		res_rd = read(STDIN_FILENO, _buff, BUFFER_READ_SIZE - 1);
		if (res_rd <= 0)
		{
			if (res_rd == -1 || (res_rd == 0 && input_len == 0))
			{
				free_input(&input, &_buff);
				*n = 0;
				if (res_rd == -1)
					return (-1);
				return (0);
			}
			break;
		}
		input_len += res_rd;
		if (_buff[0] == '\n')
		{
			input_len = 1;
			res_rd = 1;
		}
		else
			_buff[res_rd] = '\0';
		save_buff(&input, &_buff, &input_len, &res_rd);
		if (isatty(0) && (_buff[0] == '\n' || _buff[res_rd - 1] == '\n'))
			break;
	}
	if (*buff != NULL)
		free(*buff);
	*buff = input;
	*n = input_len;
	free(_buff);
	return (input_len);
}


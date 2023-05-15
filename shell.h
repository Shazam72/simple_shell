#ifndef __MAIN__
#define __MAIN__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>
#include <limits.h>
#include "types_defines.h"
#include "builtin.h"

/* env.c */
char **init_env(unsigned int empty_slot);
void free_env(void);
char *_getenv(char *name);
char *_setenv(char *name, char *value, int overwrite);
int _unsetenv(char *name);

/* executor.c */
int exec_from_line(char *readed, int show_errors);
int exec_args(char **args, int show_errors);

/* helpers */
ssize_t read_line(char **buff);
ssize_t _getline(char **buff, size_t *n);

/* utils.c */
void safe_exit(char const *exit_msg, int exit_code);
void _memcpy(void *dest, void *src, size_t size);
void *_realloc(void *ptr, size_t old_size, size_t new_size);
void _print_error(char *msg, char *prefix);
int exit_interactive(char **args);

/* path.c */
char *_which(char *filename);
StringNode *get_path_list(void);

/* stringA.c */
unsigned int _strlen(char *str);
char *_strtok(char *str, char *delim);
char *_strstr(char *str, char *needle);
char *_strcat(char *dest, char *src);
char *_strcpy(char *dest, char *src);

/* stringB.c */
char *_strncpy(char *dest, char *src, unsigned int n);
StringNode *_strsplit(char *str, char *delim);
int _isInt(char *str);
int _strtoi(char *str);

/* stringC.c */
char *_strchr(char *str, char needle);
int _strcmp(char *str1, char *str2);
int _strcmp_n(char *str1, char *str2, unsigned int n);
unsigned int get_string_arr_length(char **args);

/* listsA.c */
StringNode *add_string_node(StringNode **list_head, char *str);
int get_list_length(StringNode *head);
int delete_a_node_at_given_index(StringNode **, unsigned int);
void free_list(StringNode *);
char **array_from_string_list(StringNode *head);

/* listsB.c */
void free_string_array(char **arr);

/* ops_func.c */
built_in_func get_ops_func(char *command_name);
int exec_ops_func(char *command_name, char **args);

#endif

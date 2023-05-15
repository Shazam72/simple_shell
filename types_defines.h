#ifndef __TYPES_DEFINITIONS__
#define __TYPES_DEFINITIONS__

/* Constants */
#define PROMPT_SYMBOL "$ "
#define BUFFER_READ_SIZE 1024
#define EXIT_BUILTIN_STATUS 99

extern char **environ;

/* Types definitions */
/**
 * struct StringNode - Node element of a string linked list
 * @str: string value
 * @next: pointer to next StringNode
 * @x: int member
 */
typedef struct StringNode
{
	char *str;
	struct StringNode *next;
	int x;
} StringNode;

/**
 * struct data_pars_struct - A function pointer-struct that permits constant
 * prototypes by displaying args to be parsed to func in pseudo-format
 * @arg_v: The strings generated from the array argument
 * @arg_c: The  counter tracking the argument
 * @env: The local copy of environment of a linked list
 * @alias: The node associated with alias
 * @file_name: The file name program
 * @args: The string created from getline args
 * @environment: The changed copy coming from the linked list environment
 * @my_exec_cmd_status:The status condition of last executed command
 * @str: string member
 * @x: int member
 * @next: pointer to next member
 * Return: Always Success (0)
 */
typedef struct data_pars_struct
{
	char *args;
	int my_exec_cmd_status;
	char *file_name;
	StringNode *alias;
	char **environment;
	StringNode *env;
	int arg_c;
	char **arg_v;
	char *str;
	struct StringNode *next;
	int x;
} data_t;


/**
 * struct built_in - The structure containing built-in string
 * @function_type: The command flag of the builtin function
 * @func: The function being evaluated
 * Return: Always Success (0)
 */
typedef struct built_in
{
	int (*func)(data_t *);
	char *function_type;

} table_for_built_in_function;


typedef int (*built_in_func)(char **args);

/**
 * struct Built_in_ops - paired builtin function with his command name
 * @op_name: command name
 * @func: associated function
 */
typedef struct Built_in_ops
{
	char *op_name;
	built_in_func func;
} Built_in_ops;

#endif

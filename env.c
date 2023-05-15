#include "shell.h"
#include "types_defines.h"

/**
 * _getenv - get at env variable
 * @name: env variable name (without '=')
 * Return: pointer to the env variable and its value else NULL
 */
char *_getenv(char *name)
{
	int i = 0, j = 0, name_len;
	char *var = NULL;
	char *tmp = NULL;

	if (name == NULL)
		return (NULL);
	name_len = _strlen(name);
	tmp = (char *)malloc(name_len + 2);
	if (tmp == NULL)
		return (NULL);
	_strcpy(tmp, name);
	_strcat(tmp, "=");
	for (i = 0; environ[i]; i++)
	{
		for (j = 0; j < name_len && environ[i][j] == tmp[j]; j++)
			;
		if (environ[i][j] != tmp[j])
			continue;
		var = environ[i];
		break;
	}
	free(tmp);
	return (var);
}

/**
 * init_env - initialize the env
 * @add_n_slot: number of empty slot
 * Return: pointer to array of env variables
 */
char **init_env(unsigned int add_n_slot)
{
	char **env = NULL;
	unsigned int env_len = 0, i = 0;

	env_len = get_string_arr_length(environ);
	env = (char **)malloc(sizeof(*env) * (env_len + add_n_slot + 1));
	if (env == NULL)
		return (NULL);
	for (i = 0; i < env_len; i++)
	{
		int var_len = _strlen(environ[i]);

		env[i] = (char *)malloc(sizeof(*env[i]) * var_len + 1);
		if (env[i] == NULL)
		{
			for (; i != 0; i--)
				free(env[i]);
			free(env[0]);
			free(env);
			return (NULL);
		}
		_strcpy(env[i], environ[i]);
	}
	env[env_len] = NULL;
	return (env);
}

/**
 * free_env - free all allocated memory of env
 * Return: 0 on success otherwise 1 if error
 */
void free_env(void)
{
	int i = 0;

	for (i = 0; environ[i]; i++)
		free(environ[i]);
	free(environ);
}

/**
 * _setenv - set a env variable
 * @name: variable name
 * @value: variable value
 * @overwrite: should overwrite (0 for no, any number for yes)
 * Return: pointer to the newly created variable else NULL
 */
char *_setenv(char *name, char *value, int overwrite)
{
	char *var = NULL;
	char **env = NULL;
	int name_len = 0,
	    i = 0, j = 0;
	unsigned int env_len = 0;

	if (name == NULL)
		return (NULL);
	var = _getenv(name);
	if (var != NULL && overwrite == 0)
		return (var);

	name_len = _strlen(name);
	var = (char *)malloc(sizeof(char) * (name_len + _strlen(value) + 2));
	if (var == NULL)
		return (NULL);
	_strcpy(var, name);
	_strcpy(var + name_len, "=");
	for (; environ[i]; i++)
	{
		for (j = 0; j < name_len && environ[i][j] == var[j]; j++)
			;
		if (environ[i][j] != var[j])
			continue;
		_strcat(var, value);
		free(environ[i]);
		environ[i] = var;
		return (var);
	}
	env = init_env(1);
	if (env == NULL)
		safe_exit("Unsufficent memory", 99);
	_strcat(var, value);
	env_len = get_string_arr_length(environ);
	env[env_len] = var;
	env[env_len + 1] = NULL;
	free_env();
	environ = env;
	return (var);
}

/**
 * _unsetenv - unset env variable
 * @name: name of variable
 * Return: O if success else 1
 */
int _unsetenv(char *name)
{
	char *env_var = NULL;
	unsigned int env_len = 0, i = 0, j = 0;
	char **env = NULL;

	if (name == NULL)
		return (1);
	env_var = _getenv(name);
	if (env_var == NULL)
		return (1);
	env_len = get_string_arr_length(environ);

	env = (char **) malloc(sizeof(*env) * env_len);
	for (i = 0; i < env_len; i++)
	{
		int var_len = 0;

		if (_strcmp(env_var, environ[i]) == 0)
		{
			j = 1;
			continue;
		}
		var_len = _strlen(environ[i]);
		env[i - j] = (char *)malloc(sizeof(char) * (var_len + 1));
		if (env[i - j] == NULL)
		{
			for (; i != 0; i--)
				free(env[i]);
			free(env[0]);
			free(env);
			return (1);
		}
		_strcpy(env[i - j], environ[i]);
	}
	env[i - 1] = NULL;
	free_env();
	environ = env;
	return (0);
}

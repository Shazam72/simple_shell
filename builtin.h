#ifndef __BUILTIN__
#define __BUILTIN__

#include "types_defines.h"

int print_env(char **args);
int _setenv_cmd(char **args);
int _unsetenv_cmd(char **args);
int exit_bultin(char **args);
int _cd(char **args);

#endif

#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>
#include <limits.h>
#include <signal.h>

enum macros {FALSE, TRUE, NEITHER, MATCH, PREFIX, EXIT_SHELL, EXIT_SHELL_CODE,
	     SKIP_FORK, DO_EXECVE};

int command_manager(char **args, int *status);

int built_ins(char **args, int *status);

int and_or(char **args, char operator, int last_compare, int *status);

int check_command(char **args, char **path_var);

int execute_command(char **args, int *status);

char *parser(char *old_buf, size_t old_size);

int _strlen(char *str);

char *_strdup(char *src);

char *str_concat(char *s1, char *s2);

int str_compare(char *s1, char *s2, int pref_or_match);

char *get_array_element(char **array, char *element_name);

/*char **make_array(char *str, char delim);*/
char **make_array(char *str, char delim, char **if_sep);

int list_len(char **list, char *entry);

char **array_cpy(char **old_array);

int _setenv(const char *name, const char *value, int overwrite);

int _unsetenv(const char *name);

int change_dir(char *name);

char *_itoa(int n);

int _atoi(char *s);

#endif

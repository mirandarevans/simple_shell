#ifndef SH_H
#define SH_H

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

#define TRUE 1
#define FALSE 0

#define DO_EXECVE 2
#define EXIT_SHELL 3
#define EXIT_SHELL_CODE 4
#define SKIP_FORK 5
#define SEP 6
#define SEP_SKIP_FORK 7

int _strlen(char *str);

char *_strdup(char *src);

char *str_search(char *needle, char *haystack);

void _strconcat(char **buffer, char *str1, char *str2);

int str_compare(char *s1, char *s2);

char *get_array_element(char **array, char *element_name);

char **make_array(char *str, char delim);

int list_len(char **list, char *entry);

char **array_cpy(char **old_array);

char *_itoa(int n);

int _atoi(char *s);

int built_ins(char **args, int *i);

int _setenv(const char *name, const char *value, int overwrite);

int _unsetenv(const char *name);

int change_dir(char *name);

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);

int execute_command(char **args, char **path_ptr, char *buf, char *buf_end);

#endif

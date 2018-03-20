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

#define TRUE 1
#define FALSE 0

int _strlen(char *str);

void str_cmb(char **buffer, char *str1, char *str2);

char *_strdup(char *src);

/*char **get_path(void);*/
char **make_array(char *str, char delim);

int str_compare(char *s1, char *s2);

void prepend(char c, char *buffer);

ssize_t _getline(char **lineptr, size_t *n, int fd);

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);

void err_exit(char *prog, char err_type);

int _atoi(char *s);

void exit_command(char *num);

char *str_search(char *needle, char *haystack);

/*char *_getenv(char *env_var);*/
char *get_array_element(char **array, char *element_name);

int list_len(char **list, char *entry);

/*void _setenv(const char *name, const char *value, int overwrite);*/

int built_ins(char **args, int i);

char *_itoa(int n);

char **array_cpy(char **old_array);

/*extern char **environ;*/
/*extern char **my_environment;*/
/*my_environment = array_cpy(environ);*/

#endif

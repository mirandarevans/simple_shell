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

#define TRUE 1
#define FALSE 0

int _strlen(char *str);

void str_cmb(char **buffer, char *str1, char *str2);

char *_strcpy(char *src);

char **get_path(void);

int str_compare(char *s1, char *s2);

void prepend(char c, char *buffer);

#endif

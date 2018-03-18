#include "shell.h"

int str_compare(char *s1, char *s2)
{
	while (*s1 != '\0' && *s2 != '\0')
	{
		if (*s1 != *s2)
			return (FALSE);
		s1++;
		s2++;
	}
	if (*s1 != *s2)
		return (FALSE);

	return(TRUE);
}

void str_cmb(char **buffer, char *str1, char *str2)
{
	char *ptr = *buffer;

	while (*str1 != '\0')
	{
		*ptr = *str1;
		ptr++;
		str1++;
	}
	while (*str2 != '\0')
	{
		*ptr = *str2;
		ptr++;
		str2++;
	}

	*ptr = '\0';
}
/*
void prepend(char c, char *buffer)
{
	char *ptr = buffer;

	while (*ptr != '\0')
		ptr++;

	while (ptr != buffer)
	{
		*(ptr + 1) = *ptr;
		ptr--;
	}
	*(ptr + 1) = *ptr;
	*ptr = c;
}
*/
/*
ssize_t getline(char **lineptr, size_t *n, int fd)
{
	char *buf = NULL;
	int r;

	r = read(fd, *lineptr, *n);
	if (r == -1)
	{
		write(STDERR_FILENO, "getline failed\n", 15);
		_exit(EXIT_FAILURE);
	}
	if (r < n)
		return (r);
	buf = malloc(*n);
	if (buf == 0)
	{
		write(STDERR_FILENO, "malloc failed\n", 14)
		_exit(EXIT_FAILURE);
	}

	while (r > *n)
	{
		r = read(fd, *lineptr, *n);
	}
}*/

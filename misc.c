#include "shell.h"

void err_exit(char *prog, char err_type)
{
	switch (err_type) {
	case 'm':
		write(STDERR_FILENO, prog, 20);
		perror(": malloc failed\n");
		exit(EXIT_FAILURE);
		break;
	case 'g':
		write(STDERR_FILENO, prog, 20);
		perror(": getline failed\n");
		exit(EXIT_FAILURE);
		break;
	case 'f':
		write(STDERR_FILENO, prog, 20);
		perror(": fork failed\n");
		exit(EXIT_FAILURE);
		break;
	case 'n':
		write(STDERR_FILENO, prog, 20);
		perror(": no such file or directory\n");
		exit(EXIT_FAILURE);
		break;
	case 'e':
		write(STDERR_FILENO, prog, 20);
		perror(": flush failed\n");
		exit(EXIT_FAILURE);
		break;
	default:
		break;
	}
}

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

ssize_t _getline(char **lineptr, size_t *n, int fd)
{
	char *buffer = NULL;
	char *ptr;
	int r;
	int i = 0;

	r = read(fd, *lineptr, *n);
	if (r == -1)
		err_exit("./hsh", 'g');

	if (r < (int)*n)
	{
		if (fflush(NULL) != 0)
			err_exit("./hsh", 'e');
		
		return (r);
	}
	buffer = malloc(*n);
	if (buffer == NULL)
		err_exit("./hsh", 'm');

	str_cmb(&buffer, *lineptr, "");
	i = r;
	while (r == (int)*n)
	{
		r = read(fd, *lineptr, *n);
		if (r == -1)
			err_exit("./hsh", 'g');
		if (_realloc(buffer, (unsigned)i, (unsigned)(i + r)) == NULL)
			err_exit("./hsh", 'm');
		ptr = buffer + i;
		str_cmb(&ptr, *lineptr, "");
		i += r;
	}
	 if (fflush(NULL) != 0)
		err_exit("./hsh", 'e');

	free(*lineptr);
	lineptr = &buffer;

	return i;
}

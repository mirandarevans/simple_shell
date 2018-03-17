#include "shell.h"

#define TRUE 1
#define FALSE 0
/*
int check_path(char *str)
{
	char *p = "/bin/";
	int is_same = TRUE;

	while (*p != '\0')
	{
		if (*str != *p)
			is_same = FALSE;

		str++;
		p++;
	}

	return (is_same);
}
*/
void str_cmb(char **buffer, char *str1, char *str2)
{
	char *ptr = *buffer;

	while (*str1 != '\0')
	{
		*ptr = *str1;
		ptr++;
		str1++;
	}

	*ptr = '/';
	ptr++;

	while (*str2 != '\0')
	{
		*ptr = *str2;
		ptr++;
		str2++;
	}

	*ptr = '\0';
}

/* remember to account for many arguments */
int main(void)
{
	int status;
	char *buf = NULL;
	size_t buf_size = 100;
	pid_t pid;
	int bytes_read;
	char *args[5];
	char *ptr;
/*	struct stat st;*/
	int i = 0;
	char **path_var = get_path();
	extern char **environ;

	buf = malloc(buf_size + 1);
	if (buf == NULL)
	{
		perror("malloc failed\n");
		exit(EXIT_FAILURE);
	}

	while (1)
	{
		args[1] = NULL;
		args[2] = NULL;
		args[3] = NULL;
		args[4] = NULL;
		i = 1;
		write(STDOUT_FILENO, "#cisfun$ ", 9);
		bytes_read = getline(&buf, &buf_size, stdin);
		buf[bytes_read - 1] = '\0';
		ptr = buf;
		while (*ptr != '\0')
		{
			if (*ptr == ' ')
			{
				*ptr = '\0';
				ptr++;
				args[i] = ptr;
				if (i < 4)
					i++;
			}
			ptr++;
		}
		if (bytes_read == -1)
		{
			write(STDERR_FILENO, "getline failed\n", 14);
			_exit(EXIT_FAILURE);
		}
		pid = fork();
		if (pid == -1)
		{
			write(STDERR_FILENO, "fork failed\n", 12);
			_exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
while (*path_var != NULL)
{
	printf("%s\n", *path_var);
	path_var++;
}

			if (access(buf, X_OK) != 0)
			{
				args[0] = malloc(100);
				while (*path_var != NULL && access(args[0], X_OK) != 0)
				{
					str_cmb(&args[0], *path_var, buf);
printf("%sX\n", args[0]);
					path_var++;
if (*path_var == NULL)
	printf("NULL\n");
printf("%sX\n", *path_var);
				}
			}
			else
				args[0] = buf;
			execve(args[0], args, environ);
			write(STDERR_FILENO, "./shell: No such file or directory\n", 35);
			_exit(EXIT_FAILURE);
		}
		wait(&status);
	}
	free(path_var);
	free(buf);
	free(args[0]);

	return(0);
}

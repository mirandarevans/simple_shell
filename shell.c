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
	char **path_ptr;
	extern char **environ;

	buf = malloc(buf_size + 1);
	if (buf == NULL)
	{
		perror("malloc failed\n");
		exit(EXIT_FAILURE);
	}

	while (1)
	{
		path_ptr = path_var;
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
				if (i < 3)
					i++;
			}
			ptr++;
		}
		if (bytes_read == -1)
		{
			write(STDERR_FILENO, "getline failed\n", 14);
			_exit(EXIT_FAILURE);
		}
		if (access(buf, F_OK) != 0)
		{
			args[0] = malloc(100);
			while (*path_ptr != NULL && access(args[0], F_OK) != 0)
			{
				str_cmb(&args[0], *path_ptr, buf);
				path_ptr++;
			}
		}
		else
			args[0] = buf;
		pid = fork();
		if (pid == -1)
		{
			write(STDERR_FILENO, "fork failed\n", 12);
			_exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
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

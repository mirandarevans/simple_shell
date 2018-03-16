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

	ptr = '\0';
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
	struct stat st;
	int i;

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
			if (stat(buf, &st) != 0)
			{
				args[0] = malloc(bytes_read + 5);
				str_cmb(&args[0], "/bin/", buf);
				if (stat(args[0], &st) != 0)
			{
					write(STDERR_FILENO, "./shell: No such file or directory\n", 35);
					_exit(EXIT_FAILURE);
				}
			}
			else
				args[0] = buf;
/*printf("%s\n", args[0]);
printf("%s\n", args[1]);
printf("%s\n", args[2]);*/
			execve(args[0], args, NULL);
			write(STDERR_FILENO, "./shell: No such file or directory\n", 35);
			_exit(EXIT_FAILURE);
		}
		wait(&status);
	}
	free(buf);
	free(args[0]);

	return(0);
}

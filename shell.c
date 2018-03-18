#include "shell.h"

int main(void)
{
	int status;
	char *buf = NULL;
	size_t buf_size = 100;
	pid_t pid;
	int bytes_read;
	char **args = NULL;
	char *ptr;
	int i;
	char **path_var = get_path();
	char **path_ptr;
	extern char **environ;
	char *tmp;

	buf = malloc(buf_size + 1);
	if (buf == NULL)
	{
		perror("malloc failed\n");
		exit(EXIT_FAILURE);
	}

	while (1)
	{
		tmp = NULL;
		path_ptr = path_var;
		write(STDOUT_FILENO, "#cisfun$ ", 9);
		bytes_read = getline(&buf, &buf_size, stdin);
		if (str_compare(buf, "exit\n") == TRUE)
			break;
		if (bytes_read == -1)
		{
			write(STDERR_FILENO, "getline failed\n", 14);
			_exit(EXIT_FAILURE);
		}
		buf[bytes_read - 1] = '\0';
		if (buf[0] != '/')
		{
			tmp = malloc(buf_size + 1);
			if (tmp == NULL)
			{
				perror("malloc failed\n");
				exit(EXIT_FAILURE);
			}
			str_cmb(&tmp, "/", buf);
			free(buf);
			buf = tmp;
		}
		ptr = buf;
		i = 2;
		while (*ptr != '\0')
		{
			if (*ptr == ' ')
				i++;
			ptr++;
		}
		args = malloc(sizeof(char *) * i);
		if (args == NULL)
		{
			write(STDERR_FILENO, "malloc failed\n", 14);
			_exit(EXIT_FAILURE);
		}
		ptr = buf;
		i = 1;
		while (*ptr != '\0')
		{
			if (*ptr == ' ')
			{
				*ptr = '\0';
				ptr++;
				args[i] = ptr;
				i++;
			}
			ptr++;
		}
		args[0] = NULL;
		ptr = buf;
		args[0] = malloc(100);
		if (args[0] == NULL)
		{
			perror("malloc failed\n");
			exit(EXIT_FAILURE);
		}
		str_cmb(&args[0], buf, "");
		args[i] = NULL;
			while (*path_ptr != NULL && access(args[0], X_OK) != 0)
			{
				str_cmb(&args[0], *path_ptr, buf);
				path_ptr++;
			}
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
		free(args[0]);
		free(args);
	}
	free(path_var);
	free(buf);

	return(0);
}

#include "shell.h"

int main(void)
{
	int status;
	char *buf = NULL;
	size_t buf_size = 100;
	pid_t pid;
	int bytes_read;
	char **args = NULL;
	char *path_str = _strcpy((char *)getenv("PATH"));
	char **path_var = make_array(path_str, ':');
	char **path_ptr;
	extern char **environ;
	char *tmp;

	buf = malloc(buf_size + 1);
	if (buf == NULL)
		err_exit("./hsh", 'm');

	while (1)
	{
		tmp = NULL;
		path_ptr = path_var;
		write(STDOUT_FILENO, "#cisfun$ ", 9);
		bytes_read = getline(&buf, &buf_size, stdin);
		
		if (bytes_read == -1)
			err_exit("./hsh", 'g');

		buf[bytes_read - 1] = '\0';
		if (buf[0] != '/')
		{
			tmp = malloc(buf_size + 1);
			if (tmp == NULL)
				err_exit("./hsh", 'm');

			str_cmb(&tmp, "/", buf);
			free(buf);
			buf = tmp;
		}
		args = make_array(buf, ' ');
		if (str_compare(buf, "/exit") == TRUE && args[1] != NULL)
			exit_command(args[1]);
		else if (str_compare(buf, "/exit") == TRUE)
			exit_command("0");

		args[0] = NULL;
		args[0] = malloc(100);
		if (args[0] == NULL)
			err_exit("./hsh", 'm');

		str_cmb(&args[0], buf, "");
		while (*path_ptr != NULL && access(args[0], X_OK) != 0)
		{
			str_cmb(&args[0], *path_ptr, buf);
			path_ptr++;
		}
		pid = fork();
		if (pid == -1)
		{
			err_exit("./hsh", 'f');
		}
		else if (pid == 0)
		{
			execve(args[0], args, environ);
			err_exit("./hsh", 'n');
		}
		wait(&status);
		free(args[0]);
		free(args);
	}
	free(path_str);
	free(path_var);
	free(buf);

	return(0);
}

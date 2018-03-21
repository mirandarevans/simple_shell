#include "shell.h"

int main(void)
{
	int status = 0;
	int bytes_read;
	int i;
	size_t buf_size = 1;
	char *buf = NULL;
	char *buf_end;
	char *tmp;
	char **args = NULL;
	char **args_ptr;
	char **args_tmp;
	extern char **environ;
	char *path_str;
	char **path_var;
	char **path_ptr;

	/*signal(SIGINT,SIG_IGN);*/

	buf = malloc(1);
	if (buf == NULL)
		exit(EXIT_FAILURE);

	while (1)
	{
		path_str = _strdup(get_array_element(environ, "PATH") + 5);
		path_var = make_array(path_str, ':');
		path_ptr = path_var;

		if (isatty(STDIN_FILENO) == 1)
			write(STDOUT_FILENO, "#cisfun$ ", 9);

		bytes_read = getline(&buf, &buf_size, stdin);

		if (bytes_read == -1)
			exit(EXIT_FAILURE);

		buf[bytes_read - 1] = '\0';

		if (buf[0] != '/')
		{
			tmp = malloc(buf_size);
			if (tmp == NULL)
				exit(EXIT_FAILURE);
			_strconcat(&tmp, "/", buf);
			free(buf);
			buf = tmp;
		}
		buf_end = buf + _strlen(buf);
		args = make_array(buf, ' ');

		args[0] = malloc(PATH_MAX + buf_size + 1);
		if (args[0] == NULL)
			exit(EXIT_FAILURE);

		_strconcat(&args[0], buf, "");

		i = built_ins(args, &status);
		args_ptr = args;
		tmp = buf;
		while (i == SEP || i == SEP_SKIP_FORK)
		{

			args_tmp = args_ptr;
			while (*args_tmp != NULL)
				args_tmp++;

			args_tmp++;
			if (i == SEP)
				status = execute_command(args_ptr, path_ptr, tmp, buf_end);

			args_ptr = args_tmp;
			tmp = args_ptr[0];
			if (*tmp != '/')
			{
				tmp--;
				*tmp = '/';
			}
			args_ptr[0] = malloc(PATH_MAX + buf_size + 1);
			if (args_ptr[0] == NULL)
				exit(EXIT_FAILURE);

			_strconcat(&args_ptr[0], tmp, "");

			i = built_ins(args_ptr, &status);
		}
		if (i == DO_EXECVE)
			status = execute_command(args_ptr, path_ptr, tmp, buf_end);

		free(args);
		free(path_str);
		free(path_var);

		if (i == EXIT_SHELL_CODE || i == EXIT_SHELL)
			break;
	}
	free(buf);

	if (i == EXIT_SHELL_CODE)
		return (status);

	return (0);
}

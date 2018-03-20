#include "shell.h"

int main(void)
{
	int status;
	char *buf = NULL;
	size_t buf_size = 100;
	pid_t pid;
	int bytes_read;
	char **args = NULL;
	char **args_ptr;
	extern char **environ;
	char **my_environment = environ;
	/*char *path_str = _strcpy((char *)getenv("PATH"));*/
	char *path_str/* = _strdup(get_array_element(my_environment, "PATH"))*/;
	char **path_var/* = make_array(path_str, ':')*/;
	char **path_ptr;
	/*extern char **environ;
	  static char **my_environment = NULL;*/
	char *tmp;

	/*my_environment = array_cpy(environ);*/

	buf = malloc(buf_size + 1);
	if (buf == NULL)
		err_exit("./hsh", 'm');

	while (1)
	{
		path_str = _strdup(get_array_element(my_environment, "PATH"));
		path_var = make_array(path_str, ':');
		path_ptr = path_var;
		tmp = NULL;
		if (isatty(STDIN_FILENO) == 1)
			write(STDOUT_FILENO, "#cisfun$ ", 9);

		bytes_read = getline(&buf, &buf_size, stdin);

		if (bytes_read == -1)
			exit(EXIT_FAILURE);

		buf[bytes_read - 1] = '\0';
		if (buf[0] != '/')
		{
			/*buf_size++;*/
			tmp = malloc(buf_size);
			if (tmp == NULL)
				err_exit("./hsh", 'm');

			str_cmb(&tmp, "/", buf);
			free(buf);
			buf = tmp;
		}
		args = make_array(buf, ' ');
		/*if (str_compare(buf, "/exit") == TRUE && args[1] != NULL)
			exit_command(args[1]);
		else if (str_compare(buf, "/exit") == TRUE)
			exit_command("0");
		else if (str_compare(buf, "/setenv") == TRUE && args[1] != NULL && args[2] != NULL)
			_setenv(args[1], args[2], 1);
		else*/
		args[0] = NULL;
		args[0] = malloc(100);
		if (args[0] == NULL)
			err_exit("./hsh", 'm');

		str_cmb(&args[0], buf, "");
		if (built_ins(args, status) == FALSE)
		{
			while (*path_ptr != NULL && access(args[0], X_OK) != 0)
			{
				str_cmb(&args[0], *path_ptr, buf);
				path_ptr++;
			}
			pid = fork();
		}
		if (pid == -1)
		{
			err_exit("./hsh", 'f');
		}
		else if (pid == 0)
		{
			execve(args[0], args, my_environment);
			err_exit(buf, 'n');
			/*fflush(NULL);
			exit(EXIT_FAILURE);*/
		}
		wait(&status);
		args_ptr = args;
		while (*args_ptr != NULL)
		{
			if (*args_ptr < buf || *args_ptr > buf + (buf_size - 1))
				free(*args_ptr);

			args_ptr++;
		}
		/*free(args[0]);*/
		free(args);
		free(path_str);
		free(path_var);
	}
	/*free(path_str);
	  free(path_var);*/
	args_ptr = my_environment;
	while (*args_ptr != NULL)
	{
		free(*args_ptr);
		args_ptr++;
	}
	free(*args_ptr);
	free(my_environment);
	free(buf);

	return(0);
}

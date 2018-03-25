#include "shell.h"

int status = 0;

int err_num = 1;

char *shell_name = NULL;

/**
 * main - executes commands from the terminal
 *
 * Return: 0, or another number if desired
 */
int main(int ac, char **av)
{
	int bytes_read;
	int is_separated = FALSE;
	int i;
	size_t buf_size = 1;
	char *buf = NULL;
	char *buf_ptr;
	char *buf_tmp;
	char **args = NULL;

	ac = ac;

	shell_name = _strdup(*av);

	environ = array_cpy(environ, list_len(environ, NULL));

	/*signal(SIGINT,SIG_IGN);*/

	buf = malloc(1);
	if (buf == NULL)
		exit(EXIT_FAILURE);

	while (1)
	{
		if (is_separated == FALSE)
		{
			if (isatty(STDIN_FILENO) == 1)
				write(STDOUT_FILENO, "my_shell$ ", 10);

			bytes_read = getline(&buf, &buf_size, stdin);
			if (bytes_read == -1)
				exit(EXIT_FAILURE);

			buf = input_san(buf, buf_size);
			buf_ptr = buf;
		}
		else
			buf_ptr = buf_tmp;

		buf_tmp = NULL;
		args = make_array(buf_ptr, ' ', &buf_tmp);
		if (buf_tmp != NULL)
			is_separated = TRUE;
		else
			is_separated = FALSE;

		i = command_manager(args);
		if (i == FALSE && is_separated == FALSE)
			err_num++;

		free(args);

		if (i == EXIT_SHELL || i == EXIT_SHELL_CODE)
			break;
	}
	free(buf);
	alias_func(NULL, TRUE);
	free_array(environ);
	free(shell_name);

	if (i == EXIT_SHELL_CODE)
		return (status % 255);

	return (0);
}

#include "shell.h"

int status;

/**
 * command_manager - manages the process a command goes through to get executed
 * @args: command and arguments
 *
 * Return: TRUE if success, FALSE if failure
 */
int command_manager(char **args)
{
	char **args_ptr = args;
	int prev_eval = NEITHER;
	int no_err = TRUE;
	char prev_op = 'c';
	char next_op = 'c';
	int what_do;

	while (*args != NULL && prev_eval != EXIT_SHELL && prev_eval != EXIT_SHELL_CODE)
	{
		while (*args_ptr != NULL && **args_ptr != '&' && **args_ptr != '|')
			args_ptr++;

		if (str_compare(*args_ptr, "||", MATCH) == TRUE)
		{
			*args_ptr = NULL;
			args_ptr++;
			next_op = '|';
		}
		if (str_compare(*args_ptr, "&&", MATCH) == TRUE)
		{
			*args_ptr = NULL;
			args_ptr++;
			next_op = '&';
		}
		if (next_op == 'c')
			break;

		prev_eval = and_or(args, prev_op, prev_eval);
		if (prev_eval == FALSE)
			no_err = FALSE;
		prev_op = next_op;
		args = args_ptr;
	}

	if (next_op == 'c')
	{
		what_do = execute_command(args);

		if (what_do == EXIT_SHELL)
			return (EXIT_SHELL);

		if (what_do == EXIT_SHELL_CODE)
			return (EXIT_SHELL_CODE);
	}

	if (no_err == FALSE || what_do == FALSE)
		return (FALSE);

	return (TRUE);
}

/**
 * built_ins - checks if a command is a built in
 * @args: command and arguments
 *
 * Return: SKIP_FORK if built in, DO_EXECVE if not a built in, EXIT_SHELL if
 * exit shell, EXIT_SHELL_CODE if exiting with a particular code
 */
int built_ins(char **args)
{
	char **args_ptr = args;
	int i;

	while (*args_ptr != NULL)
	{
		if (**args_ptr == '$')
                {
                        if (str_compare("$?", *args_ptr, MATCH) == TRUE)
                                *args_ptr = _itoa(status);
                }
                if (**args_ptr == '#')
                {
                        *args_ptr = NULL;
			break;
                }
		args_ptr++;
	}
	i = alias_func(args, FALSE);
	if (i == DO_EXECVE)
		return (DO_EXECVE);
	if (i == SKIP_FORK)
		return (SKIP_FORK);
	if (i == FALSE)
	{
		status = 1;
		return (SKIP_FORK);
	}

	if (str_compare("exit", *args, MATCH) == TRUE && args[1] != NULL)
	{
		status = _atoi(args[1]);
		return (EXIT_SHELL_CODE);
	}
	else if (str_compare("exit", *args, MATCH) == TRUE)
	{
		return (EXIT_SHELL);
	}
	else if (str_compare("setenv", *args, MATCH) == TRUE && args[1] != NULL && args[2] != NULL)
	{
		status = _setenv(args[1], args[2], 1);
		return (SKIP_FORK);
	}
	else if (str_compare("unsetenv", *args, MATCH) == TRUE && args[1] != NULL)
	{
		status = _unsetenv(args[1]);
		return (SKIP_FORK);
	}
	else if (str_compare("cd", *args, MATCH) == TRUE)
	{
		status = change_dir(args[1]);
		if (status == 2)
			err_message(args);
		return (SKIP_FORK);
	}
	else if (str_compare("env", *args, MATCH) == TRUE)
	{
		status = print_env();
		return (SKIP_FORK);
	}

	return (DO_EXECVE);
}

/**
 * and_or - deals with command line logical operators
 * @args: command and arguments
 * @last_compare: if last command in logic evaluated to true or false
 */
int and_or(char **args, char operator, int last_compare)
{
	int i;

	if (last_compare == NEITHER)
	{
		i = execute_command(args);
		if (i == EXIT_SHELL)
			return (EXIT_SHELL);
		if (i == EXIT_SHELL_CODE)
			return (EXIT_SHELL_CODE);
		if (i == TRUE)
			return (TRUE);

		return (FALSE);
	}
	if (last_compare == TRUE && operator == '&')
	{
		i = execute_command(args);
		if (i == EXIT_SHELL)
                        return (EXIT_SHELL);
                if (i == EXIT_SHELL_CODE)
                        return (EXIT_SHELL_CODE);
		if (i == TRUE)
			return (TRUE);
	}

	if (last_compare == FALSE && operator == '|')
	{
		i = execute_command(args);
		if (i == EXIT_SHELL)
                        return (EXIT_SHELL);
                if (i == EXIT_SHELL_CODE)
                        return (EXIT_SHELL_CODE);
		if (i == TRUE)
			return (TRUE);
	}

	return (FALSE);
}

/**
 * check_command - checks if a non-built-in exists
 * @args: argument and commands
 * @path_var: the PATH var in list form
 *
 * Return: TRUE if valid command, FALSE if not
 */
char *check_command(char **args, char **path_var)
{
	char *command_buf;
	char *full_buf;

	if (**args != '/' || **args != '.')
		command_buf = str_concat("/", *args);
	else
		command_buf = _strdup(*args);

	full_buf = _strdup(command_buf);

	while (*path_var != NULL && access(full_buf, X_OK) != 0)
	{
		free(full_buf);
		full_buf = str_concat(*path_var, command_buf);
		path_var++;
	}

	if (access(full_buf, X_OK) != 0)
	{
		status = 127;
		err_message(args);
		free(command_buf);
		free(full_buf);
		return (NULL);
	}

	free(command_buf);
	return (full_buf);
}

/**
 * execute_command - executes a command
 * @args: command and arguments
 *
 * Return: TRUE if success, FALSE if not
 */
int execute_command(char **args)
{
	char *path_str;
	char **path_var;
	char *buf_ptr = *args;
	char *command_name;
	pid_t pid;
	int what_do = built_ins(args);

	if (what_do == DO_EXECVE)
	{
		if (get_array_element(environ, "PATH") != NULL)
			path_str = _strdup(get_array_element(environ, "PATH") + 5);

		path_var = make_array(path_str, ':', NULL);

		command_name = check_command(args, path_var);
		if (command_name == NULL)
			return (FALSE);

		pid = fork();

		if (pid == -1)
		{
			exit(EXIT_FAILURE);
		}
		if (pid == 0)
		{
			execve(command_name, args, environ);
			exit(EXIT_FAILURE);
		}
		wait(&status);

		free(command_name);
		free(path_str);
		free(path_var);
	}

	if (*args != buf_ptr)
		free(*args);
	args++;

	while (*args != NULL)
	{
		while (*buf_ptr != '\0')
		{
			buf_ptr++;
		}
		buf_ptr++;

		if (*args != buf_ptr)
			free (*args);

		args++;
	}

	if (what_do == EXIT_SHELL)
		return (EXIT_SHELL);

	if (what_do == EXIT_SHELL_CODE)
		return (EXIT_SHELL_CODE);

	if (status != 0)
		return (FALSE);

	return (TRUE);
}

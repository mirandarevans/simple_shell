#include "shell.h"

/**
 * built_ins - manages the built-in commands
 * @args: arguments from the command line
 * @i: an int used for the exit code if the user is exiting
 *
 * Return: an int that determines what the main process will do
 */
int built_ins(char **args, int *i)
{
	int skip_fork = FALSE;

	if (str_compare("/exit", args[0]) == TRUE && args[1] != NULL)
	{
		*i = _atoi(args[1]);
		return (EXIT_SHELL_CODE);
	}
	else if (str_compare("/exit", args[0]) == TRUE)
	{
		return (EXIT_SHELL);
	}
	else if (str_compare("/setenv", args[0]) == TRUE && args[1] != NULL && args[2] != NULL)
	{
		_setenv(args[1], args[2], 1);
		skip_fork = TRUE;
	}
	else if (str_compare("/unsetenv", args[0]) == TRUE && args[1] != NULL)
	{
		_unsetenv(args[1]);
		skip_fork = TRUE;
	}
	else if (str_compare("/cd", args[0]) == TRUE)
	{
		change_dir(args[1]);
		skip_fork = TRUE;
	}

		while (*args != NULL)
		{
			if (**args == '$')
			{
				if (*(*args + 1) == '?')
					*args = _itoa(*i);
			}
			if (**args == '#')
			{
				*args = NULL;
				if (skip_fork == TRUE)
					return (SKIP_FORK);

				return (DO_EXECVE);
			}
			if (**args == ';')
			{
				*args = NULL;
				if (skip_fork == TRUE)
					return (SEP_SKIP_FORK);

				return (SEP);
			}
			args++;
		}

	if (skip_fork == TRUE)
		return (SKIP_FORK);

	return (DO_EXECVE);
}

/**
 * _setenv - sets and environmental variable
 * @name: name of the variable
 * @value: value to set the variable to
 * @overwrite: function won't do anthing if the variable doesn't already exist
 * and overwrite is 0
 *
 * Return: 0 on success
 */
int _setenv(const char *name, const char *value, int overwrite)
{
	extern char **environ;
	char **new_environ;
	char *buffer;
	char *buf_ptr;
	char *element_ptr = get_array_element(environ, (char *) name);
	int len;

	if (element_ptr != NULL && overwrite == 0)
		exit(EXIT_FAILURE);

	buffer = malloc(_strlen((char *)name) + _strlen((char *)(value)) + 2);
	if (buffer == NULL)
		exit(EXIT_FAILURE);

	_strconcat(&buffer, (char *)name, "=");
	len = _strlen((char *)name) + 1;
	buf_ptr = buffer + len;
	_strconcat(&buf_ptr, (char *)value, "");

	if (element_ptr == NULL)
	{
		len = list_len(environ, NULL);

		new_environ = malloc(sizeof(char **) * (len + 1));
		if (new_environ == NULL)
			exit(EXIT_FAILURE);

		new_environ = array_cpy(environ);
		new_environ[len - 1] = buffer;
		new_environ[len] = NULL;
		environ = new_environ;
		return (0);

	}
	else
	{
		len = list_len(environ, (char *)name);
		environ[len] = buffer;
	}

	return (0);
}

/**
 * _unsetenv - deletes an environmental variable
 * @name: name of variable
 *
 * Return: 0 if successful
 */
int _unsetenv(const char *name)
{
	extern char **environ;
	char **env_ptr;
	int len = list_len(environ, (char *)name);

	if (len == -1)
		return (-1);

	env_ptr = environ + len;
	free(*env_ptr);
	while (*(env_ptr + 1) != NULL)
	{
		*env_ptr = *(env_ptr + 1);
		env_ptr++;
	}
	*env_ptr = NULL;

	return (0);
}

/**
 * change_dir - changes the current working directory
 * @name: name of directory to change to
 *
 * Return: 0 if successful
 */
int change_dir(char *name)
{
	extern char **environ;
	char *home;
	char *pwd;
	char path_buffer[PATH_MAX];
	size_t buf_size = PATH_MAX;
	int i;

	getcwd(path_buffer, buf_size);

	if (name == NULL || str_compare("~", name) == TRUE || str_compare("$HOME", name) == TRUE)
	{

		home = get_array_element(environ, "HOME");

		if (home == NULL)
			return (-1);

		while (*home != '=')
		{
			home++;
		}
		home++;
		i = chdir((const char *)home);
		if (i == -1)
			return (-1);

		_setenv("OLDPWD", (const char *)path_buffer, 1);
		_setenv("PWD", (const char *)home, 1);

 		return (0);
	}
	else if (str_compare("-", name) == TRUE)
	{
		pwd = get_array_element(environ, "OLDPWD");
		if (pwd == NULL)
			return (-1);

		while (*pwd != '=')
		{
			pwd++;
		}
		pwd++;

		i = chdir((const char *)pwd);
		if (i == -1)
			return (-1);

		write(STDOUT_FILENO, pwd, _strlen(pwd));
		write(STDOUT_FILENO, "\n", 1);
		_setenv("OLDPWD", (const char *)path_buffer, 1);
		_setenv("PWD", (const char *)pwd, 1);

		return (0);
	}
	else if (name != NULL)
	{
		i = chdir((const char *)name);
		if (i == -1)
			return (-1);

		_setenv("OLDPWD", (const char *)path_buffer, 1);
		_setenv("PWD", (const char *)name, 1);

		return (0);
	}

	return (-1);
}

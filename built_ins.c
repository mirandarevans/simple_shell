#include "shell.h"

int status;

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
	char **new_environ;
	char *buffer;
	char *buf_ptr;
	char *element_ptr = get_array_element(environ, (char *) name);
	int len;

	if (element_ptr != NULL && overwrite == 0)
		exit(EXIT_FAILURE);

	buffer = str_concat((char *)name, "=");
	buf_ptr = str_concat(buffer, (char *)value);
	free(buffer);
	buffer = buf_ptr;

	if (element_ptr == NULL)
	{
		len = list_len(environ, NULL);
		new_environ = array_cpy(environ, len + 1);
		new_environ[len - 1] = buffer;
		new_environ[len] = NULL;
		free_array(environ);
		environ = new_environ;
		return (0);

	}
	else
	{
		len = list_len(environ, (char *)name);
		free(environ[len]);
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
	char *home;
	char *pwd;
	char path_buffer[PATH_MAX];
	size_t buf_size = PATH_MAX;
	int i;

	getcwd(path_buffer, buf_size);

	if (str_compare("~/", name, PREFIX) == TRUE)
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
                        return (2);

		name += 2;
	}

	if (name == NULL || str_compare("~", name, MATCH) == TRUE || str_compare("$HOME", name, MATCH) == TRUE)
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
			return (2);

		_setenv("OLDPWD", (const char *)path_buffer, 1);
		_setenv("PWD", (const char *)home, 1);

		return (0);
	}
	else if (str_compare("-", name, MATCH) == TRUE)
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
			return (2);

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
                        return (2);

		_setenv("OLDPWD", (const char *)path_buffer, 1);
		_setenv("PWD", (const char *)name, 1);

		return (0);
	}
	return (2);
}

/**
 * alias_func - deals with command aliases
 * @args: arguments from command line
 * @to_free: indicated if aliases need to be freed (exiting shell);
 *
 * Return: TRUE if exiting, FALSE if the command is not "alias" or an alias,
 * SKIP_FORK if success
 */
int alias_func(char **args, int to_free)
{
	static alias head = {NULL, NULL, NULL};
	char *char_ptr;
	int no_error = TRUE;

	if (to_free == TRUE)
		return (free_aliases(head.next));

	if (str_compare("alias", *args, MATCH) != TRUE)
		return (check_if_alias(args, head.next));

	args++;

	if (*args == NULL)
		return (print_aliases(head.next));

	while (*args != NULL)
	{
		char_ptr = *args;
		while (*char_ptr != '\0' && *char_ptr != '=')
			char_ptr++;

		if (*char_ptr == '\0' || char_ptr == *args)
		{
			if (print_alias_value(*args, &head) == FALSE)
				no_error = FALSE;
		}
		else
		{
			*char_ptr = '\0';
			char_ptr++;
			set_alias_value(*args, &head, char_ptr);
			*(char_ptr - 1) = '=';
		}
		args++;
	}

	if (no_error == FALSE)
		return (FALSE);

	return (SKIP_FORK);
}

/**
 * print_env - prints the environment
 *
 * Return: TRUE
 */
int print_env(void)
{
	char **ptr = environ;

	while (*ptr != NULL)
	{
		write(STDOUT_FILENO, *ptr, _strlen(*ptr));
		write(STDOUT_FILENO, "\n", 1);
		ptr++;
	}

	return (TRUE);
}

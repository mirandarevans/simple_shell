#include "shell.h"

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

	/*buffer = malloc(_strlen((char *)name) + _strlen((char *)(value)) + 2);
	if (buffer == NULL)
		exit(EXIT_FAILURE);
	*/
	buffer = str_concat((char *)name, "=");
	buf_ptr = str_concat(buffer, (char *)value);
	free(buffer);
	buffer = buf_ptr;

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
			return (-1);

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
/*
typedef struct alias
{
	char *name;
	char *value;
	alias *next;
} alias;

int alias_func(char **args)
{
	static alias head = {NULL, NULL, NULL};
	alias *alias_ptr = head.next;
	char *char_ptr;

	args++;

	if (*args == NULL)
	{
		while (alias_ptr != NULL)
		{
			write(STDOUT_FILENO, alias_ptr->name, _strlen(alias_ptr->name));
			write(STDOUT_FILENO, "=", 1);
			write(STDOUT_FILENO, alias_ptr->value, _strlen(alias_ptr->value));
			ptr = ptr->next;
		}
		return (TRUE);
	}
	else
	{
		while (*args != NULL)
		{
			alias_ptr = &head;
			char_ptr = *args;
			while (*char_ptr != '\0' && *char_ptr != '=')
				char_ptr++;

			if (*char_ptr == '\0')
			{
				while (alias_ptr != NULL)
				{
					if (str_compare(*args, alias_ptr->name, MATCH) == TRUE)
					{
						write(STDOUT_FILENO, *args, _strlen(*args));
						write(STDOUT_FILENO, "=", 1);
						write(STDOUT_FILENO, alias_ptr->value, _strlen(alias_ptr->value));
						break;
					}
					alias_ptr = alias_ptr->next;
				}
			}
			else
			{
				while (alias_ptr->next != NULL)
				{
					alias_ptr = alias_ptr->next;
				}
				alias_ptr->next = malloc(sizeof(alias *));
				alias_ptr = alias_ptr->next;
				*char_ptr = '\0';
				alias_ptr->name = _strdup(*args);
				char_ptr++;
				alias_ptr->value = _strdup(char_ptr);
			}
			args++;
		}
	}
}
*/

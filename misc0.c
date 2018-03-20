#include "shell.h"

/**
 * _atoi - convert string to int
 * @s: string to be converted
 *
 * Return: the int that has been converted
 */
int _atoi(char *s)
{
	int n = 0;
	int is_num = FALSE;
	int sign = 1;
	int s_int;

	while (*s)
	{
		if (is_num == TRUE && (*s > '9' || *s < '0'))
			break;
		if (*s == '-')
			sign = -sign;
		if (is_num == FALSE && *s >= '1' && *s <= '9')
		{
			s_int = *s - 48;
			n += s_int;
			n *= sign;
			is_num = TRUE;
		}
		else if (*s >= '0' && *s <= '9')
		{
			s_int = *s - 48;
			if (n >= 0)
				n = (n * 10) + s_int;
			else
				n = (n * 10) - s_int;
		}
		s++;
	}

	if (is_num == FALSE)
		return (0);

	return (n);
}

void exit_command(char *num)
{
	int i = _atoi(num);

	exit(i);
}

int list_len(char **list, char *entry)
{
	int i = 0;

	if (entry == NULL)
	{
		while (*list != NULL)
		{
			i++;
			list++;
		}
		i++;
		return (i);
		}
	else
	{
		while (*list != NULL)
		{
			if (str_search(entry, *list) != NULL)
				return (i);
			i++;
			list++;
		}
	}
	return (-1);
}
/*
void _setenv(const char *name, const char *value, int overwrite)
{*/
	/*char *env_var = (char *)_getenv((char *)name);*/
	/*char **my_environment;*/
	/*char *env_var = get_array_element(my_environment, (char *)name);*/
	/*int len = list_len(environ, NULL);*/
	/*int len;*/
	/*const char *n_ptr = name;*/
	/*int index;
	char *buffer;
	char *ptr;

	if (env_var != NULL && overwrite == 0)
		err_exit("./setenv", 'e');

	buffer = malloc(_strlen((char *)name) + _strlen((char *)value) + 2);
	str_cmb(&buffer, (char *)name, "=");
	len = _strlen((char *)name);
	ptr = buffer + len;
	str_cmb(&ptr, (char *)value, "");

	if (env_var == NULL)
	{
		len = list_len(my_environment, NULL);
		my_environment = _realloc(my_environment, sizeof(char **) * len, sizeof(char **) * (len+ 1));
		if (my_environment == NULL)
			err_exit("./setenv", 'm');
		my_environment[len - 1] = buffer;
		my_environment[len] = NULL;
	}
	else
	{
		index = list_len(my_environment, (char *)name);
		free(my_environment[index]);
		my_environment[index] = buffer;
	}*/
/*
	if (env_var == NULL)
	{
		environ = _realloc(environ, sizeof(char **) * len, sizeof(char **) * (len+ 1));
		if (environ == NULL)
			err_exit("./setenv", 'm');
		environ[len - 1] = malloc(_strlen((char *)name) + _strlen((char *)value) + 2);
		if (environ[len - 1] == NULL)
			err_exit("./setenv", 'm');
		env_var = environ[len - 1];
		while (*n_ptr != '\0')
		{
			*env_var = *n_ptr;
			env_var++;
			n_ptr++;
		}
		*env_var = '=';
		environ[len] = NULL;
	}
	else if (_strlen(env_var) < _strlen((char *)name) + _strlen((char *)value) + 1)
	{
		index = list_len(environ, (char *)name);

		environ[index] = _realloc(environ[index], _strlen(env_var) + 1, _strlen((char *)name) + _strlen((char *)value) + 2);
		buffer = malloc(_strlen((char *)name) + _strlen((char *)value) + 2);
		free(environ[index]);
		if (buffer == NULL)
			err_exit("./setenv", 'm');
		env_var = buffer;
		while (*n_ptr != '\0')
		{
			*env_var = *n_ptr;
			env_var++;
			n_ptr++;
		}
		*env_var = '=';
	}

	while (*env_var != '=')
	{
		env_var++;
	}
	env_var++;
	while (*value != '\0')
	{
		*env_var = *value;
		env_var++;
		value++;
		}*/
/*}*/

int built_ins(char **args, int i)
{
	if (str_compare(args[0], "/exit") == TRUE && args[1] != NULL)
		exit_command(args[1]);
	else if (str_compare(args[0], "/exit") == TRUE)
		exit_command("0");
	/*else if (str_compare(args[0], "/setenv") == TRUE && args[1] != NULL && args[2] != NULL)
	{
		_setenv(args[1], args[2], 1);
		return (TRUE);
		}*/
	else
		while (*args != NULL)
		{
			if (**args == '$')
			{
				if (*(*args + 1) == '?')
				{
					*args = _itoa(i);
				}
			}
			if (**args == '#')
			{
				*args = NULL;
				return (FALSE);
			}
			args++;
		}

	return (FALSE);
}

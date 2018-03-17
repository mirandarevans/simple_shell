#include "shell.h"

int _strlen(char *str)
{
	int i = 0;

	while (*str != '\0')
	{
		i++;
		str++;
	}

	return (i);
}

char *_strcpy(char *src)
{
	int len = _strlen(src);
	char *dest = NULL;
	char *ptr;

	dest = malloc(len + 1);
	if (dest == NULL)
	{
		write(STDERR_FILENO, "malloc failed\n", 14);
		exit(EXIT_FAILURE);
	}

	ptr = dest;

	while (*src != '\0')
	{
		*ptr = *src;
		ptr++;
		src++;
	}

	return (dest);
}

char **get_path(void)
{
	const char *env_str = getenv("PATH");
	char *env_cpy = _strcpy((char *)env_str);
	char *env_ptr = env_cpy;
	unsigned int i = 2;
	char **env_arr = NULL;

	while (*env_ptr != '\0')
	{
		if (*env_ptr == '\n')
			i++;

		env_ptr++;
	}

	env_arr = malloc(i * sizeof(char *));
	if (env_arr == NULL)
	{
		write(STDERR_FILENO, "malloc failed\n", 14);
		exit(EXIT_FAILURE);
	}

	env_arr[0] = env_cpy;
	env_ptr = env_cpy;
	i = 1;

	while (*env_ptr != '\0')
	{
		if (*env_ptr == ':')
		{
			*env_ptr = '\0';
			env_ptr++;
			env_arr[i] = env_ptr;
			i++;
		}
		env_ptr++;
	}
	env_arr[i] = NULL;

	return (env_arr);
}


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

char *_strdup(char *src)
{
	int len = _strlen(src);
	char *dest = NULL;
	char *ptr;

	dest = malloc(len + 1);
	if (dest == NULL)
		err_exit("./hsh", 'm');

	ptr = dest;

	while (*src != '\0')
	{
		*ptr = *src;
		ptr++;
		src++;
	}

	return (dest);
}

char *str_search(char *needle, char *haystack)
{
	char *h_ptr = haystack;
	char *n_ptr;

	while (*haystack != '\0')
	{
		n_ptr = needle;
		h_ptr = haystack;
		while (*n_ptr == *h_ptr)
		{
			h_ptr++;
			n_ptr++;
		}
		if (*n_ptr == '\0')
			return (haystack);

		haystack++;
	}

	return (NULL);
}

/*char *_getenv(char *env_var)
{
	extern char **environ;
	char **env_ptr = environ;
	char *env_str;

	while (env_ptr != NULL)
	{
		env_str = str_search(env_var, *env_ptr);
		if (env_str != NULL)
			return (env_str);

		env_ptr++;
	}

	return (NULL);
	}*/

char *get_array_element(char **array, char *element_name)
{
	char *str;

	while (*array != NULL)
	{
		str = str_search(element_name, *array);
		if (str != NULL)
			return (*array);
		array++;
	}

	return (NULL);
}

char **make_array(char *str, char delim)
{
	char *str_ptr = str;
	unsigned int i = 2;
	char **array = NULL;

	while (*str_ptr != '\0')
	{
		if (*str_ptr == delim)
			i++;

		str_ptr++;
	}

	array = malloc(i * sizeof(char **));
	if (array == NULL)
		err_exit("./hsh", 'm');

	array[0] = str;
	str_ptr = str;
	i = 1;

	while (*str_ptr != '\0')
	{
		if (*str_ptr == delim)
		{
			*str_ptr = '\0';
			str_ptr++;
			array[i] = str_ptr;
			i++;
		}
		str_ptr++;
	}
	array[i] = NULL;

	return (array);
}

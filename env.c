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

	array = malloc(i * sizeof(char *));
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


#include "shell.h"

char **array_cpy(char **old_array)
{
	char **new_array = NULL;
	char **ptr_array;
	int len;

	len = list_len(old_array, NULL);
	new_array = malloc(sizeof(char **) * len);
	new_array[len - 1] = NULL;

	ptr_array = new_array;
	while (*ptr_array != NULL)
	{
		*ptr_array = _strdup(*old_array);
		ptr_array++;
		old_array++;
	}

	return (new_array);
}

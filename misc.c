#include "shell.h"

/**
 * _realloc - reallocates memory that has previously been malloc'd
 * @ptr: old ptr we are reallocating
 * @old_size: size of old memory we are reallocating
 * @new_size: size of new memory we want to reallocate
 *
 * Return: pointer to new memory, or NULL if failure
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *new_ptr = NULL;
	char *ptr_cpy;
	unsigned int i;
	char *old_ptr = (char *)ptr;

	if (new_size == old_size)
		return (ptr);

	if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}

	new_ptr = malloc(new_size);

	if (new_ptr == NULL)
		return (NULL);

	if (ptr == NULL)
		return (new_ptr);

	for (i = 0; i < old_size; i++)
	{
		*ptr_cpy = *old_ptr;
		ptr_cpy++;
		old_ptr++;
	}

	free(ptr);

	return (new_ptr);
}

int execute_command(char **args, char **path_ptr, char *buf, char *buf_end)
{
	int status;
	char **args_ptr = args;
	pid_t pid;
	extern char **environ;

	while (*path_ptr != NULL && access(args[0], X_OK) != 0)
	{
		_strconcat(&args[0], *path_ptr, buf);
		path_ptr++;
	}

	pid = fork();

	if (pid == -1)
	{
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		execve(args[0], args, environ);
		exit(EXIT_FAILURE);
	}
	wait(&status);

	while (*args_ptr != NULL)
	{
		if (*args_ptr < buf || *args_ptr > buf_end)
			free(*args_ptr);

		args_ptr++;
	}

	return (status);
}

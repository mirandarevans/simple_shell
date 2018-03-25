#include "shell.h"

int status;

int err_num;

char *shell_name;

/**
 * input_san - sanitizes input from the command line
 * @old_buf: buffer to be sanitized
 * @old_size: size of old buffer
 *
 * Return: the new, sanitized buffer
 */
char *input_san(char *old_buf, size_t old_size)
{
        char *new_buf = malloc(old_size * 3);
        char *new_ptr = new_buf;
        char *old_ptr = old_buf;

        while (*old_ptr != '\0')
        {
                if (*old_ptr == ' ')
                {
                        *new_ptr = *old_ptr;
                        new_ptr++;
                        old_ptr++;
                        while (*old_ptr != '\0' && *old_ptr == ' ')
                                old_ptr++;
                }
                else if (*old_ptr == '|' && *(old_ptr + 1) == '|')
                {
                        if (*(new_ptr - 1) != ' ')
                        {
                                *new_ptr = ' ';
                                new_ptr++;
                        }
                        *new_ptr = '|';
                        new_ptr++;
                        *new_ptr = '|';
                        new_ptr++;
                        old_ptr += 2;
                        if (*old_ptr != ' ')
                        {
                                *new_ptr = ' ';
                                new_ptr++;
                        }
                }
                else if (*old_ptr == '&' && *(old_ptr + 1) == '&')
                {
                        if (*(new_ptr - 1) != ' ')
                        {
                                *new_ptr = ' ';
                                new_ptr++;
                        }
                        *new_ptr = '&';
                        new_ptr++;
                        *new_ptr = '&';
                        new_ptr++;
                        old_ptr += 2;
                        if (*old_ptr != ' ')
                        {
                                *new_ptr = ' ';
                                new_ptr++;
                        }
                }
                else if (*old_ptr == ';')
                {
                        if (*(new_ptr - 1) != ' ')
                        {
                                *new_ptr = ' ';
                                new_ptr++;
                        }
                        *new_ptr = ';';
                        new_ptr++;
                        old_ptr++;
                        if (*old_ptr != ' ')
                        {
                                *new_ptr = ' ';
                                new_ptr++;
                        }
                }
                else
                {
                        *new_ptr = *old_ptr;
                        new_ptr++;
                        old_ptr++;
                }
        }
        *(new_ptr - 1) = '\0';
        free(old_buf);
        return (new_buf);
}

void err_message(char **args)
{
	char *err_str_num = _itoa(err_num);

	if (str_compare("cd", *args, MATCH) == TRUE)
	{
		write(STDERR_FILENO, shell_name, _strlen(shell_name));
		write(STDERR_FILENO, ": ", 2);
		write(STDERR_FILENO, err_str_num, _strlen(err_str_num));
		write(STDERR_FILENO, ": cd: can't cd to", 17);
		write(STDERR_FILENO, args[1], _strlen(args[1]));
		write(STDERR_FILENO, "\n", 1);
		return;
	}

	write(STDERR_FILENO, shell_name, _strlen(shell_name));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, err_str_num, _strlen(err_str_num));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, *args, _strlen(*args));
	write(STDERR_FILENO, ": not found\n", 12);

	free(err_str_num);
}

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

	ptr_cpy = new_ptr;

	for (i = 0; i < old_size; i++)
	{
		*ptr_cpy = *old_ptr;
		ptr_cpy++;
		old_ptr++;
	}

	free(ptr);

	return (new_ptr);
}

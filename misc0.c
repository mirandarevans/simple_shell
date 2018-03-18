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

#include "shell.h"

char *_itoa(int n)
{
	char *buf = malloc(12);
	char *ptr = buf;
	int is_min = FALSE;
	int i_mask = 1000000000;
	int digit = 0;

	if (n == INT_MIN)
	{
		*ptr = '-';
		ptr++;
		n = INT_MAX;
		is_min = TRUE;
	}

	if (n < 0)
	{
		*ptr = '-';
		ptr++;
		n = -n;
	}

	while (i_mask > 9 && digit == 0)
	{
		digit = n / i_mask;
		n %= i_mask;
		i_mask /= 10;
	}

	if (digit != 0)
	{
		*ptr = digit + '0';
		ptr++;
	}

	while (i_mask > 9)
	{
		digit = n / i_mask;
		*ptr = digit + '0';
		ptr++;
		n %= i_mask;
		i_mask /= 10;
	}

	if (is_min == TRUE)
		n += 1;

	*ptr = n + '0';
	ptr++;
	*ptr = '\0';
	return (buf);
}

int _atoi(char *s)
{
	int n = 0;
	int is_num = FALSE;
	int sign = 1;
	int s_int;

	while (*s != '\0')
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

	return (n);
}

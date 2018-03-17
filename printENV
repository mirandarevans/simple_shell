#include <stdio.h>
int main(void)
{
	extern char **environ;
	char *s;
	int i = 0;

	while(environ[i])
	{
		s = environ[i++];
		printf("%s\n",s);
	}
}

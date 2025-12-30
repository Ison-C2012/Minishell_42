#include <stdio.h>

char	*res_hello(void)
{
	return ("hello");
}

char	*res_world(void)
{
	char	*str = "world";
	return (str);
}

char	res_space(void)
{
	return (' ');
}

int	main(void)
{
	printf ("%p\n", res_hello());
	printf ("%s%c", res_hello(), res_space());
	printf ("%s", res_world());
	return 0;
}

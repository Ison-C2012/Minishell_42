#include <stdio.h>
#include <string.h>

#define NO 0
#define YES 1

int	main(int ac, char **av, char **ev)
{
	int	nl;
	int	i;

	if (ac == 1)
	{
		printf("\n");
		return 0;
	}
	i = 1;
	while (i < ac)
	{
		if (i == 1)
		{
			if (strncmp(av[i], "-n", 3) == 0)
			{
				nl = NO;
				i++;
				continue ;
			}
			else
				nl = YES;
		}
		printf ("%s", av[i]);
		i++;
		if (i < ac)
			printf(" ");
	}
	if (nl == YES)
		printf("\n");
	return (0);
}

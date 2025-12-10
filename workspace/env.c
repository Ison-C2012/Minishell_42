#include <stdio.h>

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

int	get_env_list(t_env *elst, char **ev)
{
	char	*res;
	char	**tmp;

	elst = (t_env *)malloc(sizeof(t_env));
	res = elst;
	while (*ev)
	{
		tmp = ft_split(ev, '=');
		if (!tmp)
			return (-1);
		elst->name = tmp[0];
		elst->value = tmp[1];
		elst->next = (t_env *)malloc(sizeof(t_env));
		if (!elst->next)
			return (-1);
		elst = elst->next;
	}
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	t_env	*env_list;

	if (get_env_list(env_list, envp) == -1)
	{

	}
}

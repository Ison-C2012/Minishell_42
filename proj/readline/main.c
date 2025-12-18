/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 17:21:31 by keitotak          #+#    #+#             */
/*   Updated: 2025/12/15 18:01:44 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*cc -lreadline*/

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef struct s_env
{
	char	*name;
	char	*value;
	char	*
}	t_env;

typedef struct s_sh
{
	char	*cpath;
	int		ecode;	//exit_code
	t_env	envlist;
}	t_sh;

int	main(int argc, char **argv, char **envp)
{
	t_sh	var;
	char	*rline;
	t_lst	*lst;
	int		*exit_code;

	if (argc != 1)
		return (1);
	if (ft_strncmp(argv[0], "./minishell", ft_strlen("./minishell") + 1) != 0)
		return (1);
	while (1)
	{
		rline = readline("minishell$ ");
		if (rline == NULL)
			break ;
		add_history(rline);
		lst = parse(&var, rline);
		// execution for pipeline
		var.ecode = exe(&var, lst);
		free(rline);
	}
	return (0);
}

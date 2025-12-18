/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 14:56:57 by keitotak          #+#    #+#             */
/*   Updated: 2025/12/18 14:35:16 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

t_list	*create_cmdlst(char **cmd, int nbr)
{
	t_list	*cmdlst;
	t_list	*new;

	cmdlst = ft_lstnew(*cmd++);
	while (--nbr > 0)
	{
		new = ft_lstnew(*cmd++);
		if (new == NULL)
		{
			ft_lstclear(&cmdlst, free);
			exit(EXIT_FAILURE);
		}
		ft_lstadd_back(&cmdlst, new);
	}
	return (cmdlst);
}

int	*create_pidarr(int nbr)
{
	int	*pidarr;
	int	i;

	pidarr = (int *)malloc(nbr * sizeof(int));
	if (pidarr == NULL)
		return (NULL);
	i = 0;
	while (i < nbr)
		pidarr[i++] = -1;
	return (pidarr);
}

int	*create_pipefd(int nbr)
{
	int	**pipefd;
	int	i;

	pipefd = (int **)malloc(nbr * sizeof(int *));
	if (pipefd == NULL)
		return (NULL);
	i = 0;
	while (i < nbr)
	{
		pipefd[i] = (int *)malloc(2 * sizeof(int));
		if (pipefd[i] == NULL)
			return (free_arr(pipefd), NULL);
		i++;
	}
	return (pipefd);
}

static void	init_pipex(t_pipex *p, char **av, int ac)
{
	p->infile = av[0];
	p->outfile = av[ac - 1];
	p->forkcnt = ac - 2;
//	p->pipefd = create_pipefd(p->forkcnt - 1);
	p->pidarr = create_pidarr(p->forkcnt);
	p->cmdlst = create_cmdlst(&av[1], p->forkcnt);
}

void	cleanup(t_list *lst, int *arr)
{
	ft_lstclear(&lst, free);
	free(arr);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	p;
	int		i;
	int		exit_code;

	if (argc < 3)
		return (EXIT_FAILURE);
	init_pipex(&p, &argv[1], argc - 1);
	i = 0;
	while (i < p.forkcnt)
	{
		if (pipe(p.next_pipefd) == error)
		{
			perror("pipe");
			return (EXIT_FAILURE);
		}
		if (fork_processes(&p, envp, i) == error)
		{
			close(p.next_pipefd[0]);
			close(p.next_pipefd[1]);
			cleanup(p.cmdlst, p.pidarr);
			return (EXIT_FAILURE);
		}
		close(p.next_pipefd[0]);
		close(p.next_pipefd[1]);
		p.cmdlst = p.cmdlst->next;
		i++;
	}
	exit_code = wait_for_children(p.pidarr, p.forkcnt);
	cleanup(p.cmdlst, p.pidarr);
	return (exit_code);
}

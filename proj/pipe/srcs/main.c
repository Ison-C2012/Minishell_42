/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 14:56:57 by keitotak          #+#    #+#             */
/*   Updated: 2025/12/10 16:53:47 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	init_pipex(t_pipex *p, char **av)
{
	p->infile = av[0];
	p->cmd1 = av[1];
	p->cmd2 = av[2];
	p->outfile = av[3];
	p->i_fd = -1;
	p->o_fd = -1;
	p->p_fd[0] = -1;
	p->p_fd[1] = -1;
	p->pid1 = -1;
	p->pid2 = -1;
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	p;

	if (argc < 2)
		return (EXIT_FAILURE);
	init_pipex(&p, &argv[1]);
	if (pipe(p.p_fd) == error)
	{
		perror("pipe");
		return (EXIT_FAILURE);
	}
	p.pid1 = fork_process(&p, envp, 1);
	p.pid2 = fork_process(&p, envp, 2);
	close(p.p_fd[0]);
	close(p.p_fd[1]);
	return (wait_for_children(&p));
}

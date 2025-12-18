/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 22:26:17 by keitotak          #+#    #+#             */
/*   Updated: 2025/12/17 18:54:03 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	exit_close_fds(pid_t pid1, pid_t pid2, int exit_code)
{
	close(pid1);
	close(pid2);
	exit(exit_code);
}

static void	child_in(t_pipex *p, char **ev)
{
	int	i_fd;

	close(p->p_fd[0]);
	i_fd = open(p->infile, O_RDONLY);
	if (i_fd == error)
	{
		perror(p->infile);
		close(p->p_fd[1]);
		exit(EXIT_FAILURE);
	}
	if (dup2(i_fd, STDIN) == error)
	{
		perror("dup2");
		exit_close_fds(i_fd, p->p_fd[1], EXIT_FAILURE);
	}
	if (dup2(p->p_fd[1], STDOUT) == error)
	{
		perror("dup2");
		exit_close_fds(i_fd, p->p_fd[1], EXIT_FAILURE);
	}
	exit_close_fds(i_fd, p->p_fd[1], exec_command(p->cmdlst->content, ev));
}

static void	child_mid(t_pipex *p, char **ev)
{

	if (dup2(p->p_fd[0], STDIN) < 0)
	{
		perror("dup2");
		exit_close_fds(p->p_fd[0], p->p_fd[1], EXIT_FAILURE);
	}
	if (dup2(p->p_fd[1], STDOUT) < 0)
	{
		perror("dup2");
		exit_close_fds(p->p_fd[0], p->p_fd[1], EXIT_FAILURE);
	}
	exit_close_fds(p->p_fd[0], p->p_fd[1], exec_command(p->cmdlst->content, ev));
}

static void	child_out(t_pipex *p, char **ev)
{
	int	o_fd;

	close(p->p_fd[1]);
	o_fd = open(p->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (o_fd == error)
	{
		perror(p->outfile);
		close(p->p_fd[0]);
		exit(EXIT_FAILURE);
	}
	if (dup2(p->p_fd[0], STDIN) < 0)
	{
		perror("dup2");
		exit_close_fds(o_fd, p->p_fd[0], EXIT_FAILURE);
	}
	if (dup2(o_fd, STDOUT) < 0)
	{
		perror("dup2");
		exit_close_fds(o_fd, p->p_fd[0], EXIT_FAILURE);
	}
	exit_close_fds(o_fd, p->p_fd[0], exec_command(p->cmdlst->content, ev));
}

int	fork_processes(t_pipex *p, char **ev, int n)
{
	p->child_pnbr++;
	p->pidarr[n] = fork();
	if (p->pidarr[n] < 0)
	{
		perror("fork");
		return (-1);
	}
	if (p->pidarr[n] == 0)
	{
		if (n == 0)
			child_in(p, ev);
		else if (n == p->forkcnt - 1)
			child_out(p, ev);
		else
			child_mid(p, ev);
	}
	p->cmdlst = p->cmdlst->next;
	if (p->cmdlst != NULL)
		fork_processes(p, ev, n + 1);
	return (success);
}

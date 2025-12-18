/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 19:56:05 by keitotak          #+#    #+#             */
/*   Updated: 2025/12/18 20:51:27 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

#define CHILD_PID 0

int	child(t_pipe *p, char *cmd)
{
	close(p->prev_pipefd[1]);
	if (dup2(p->prev_pipefd[0], STDIN_FILENO) == -1)
	{
		perror("dup2");
		return (-1);
	}
	close(p->next_pipefd[0]);
	if (dup2(p->next_pipefd[1], STDOUT_FILENO) == -1)
	{
		perror("dup2");
		return (-1);
	}
	return (exec(p, cmd));
}

pid_t	fork(t_pipe *p, char *cmd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (-1);
	}
	if (pid == CHILD_PID)
	{
		child(p, cmd);
		cleanup();
		exit(EXIT_FAILURE);
	}
	return (pid);
}

int	multi_pipe(int count, char **cmds)
{
	t_pipe	p;

	init(&p, count, cmds);

	while (count--)
	{
		if (pipe(p.next_pipefd) == -1)
		{
			perror("pipe");
			return (EXIT_FAILURE);
		}
		p->pid[count] = fork(&p, *cmds);
		p.prev_pipefd = p.next_pipefd;
		p
		cmds++;
	}
	wait(p->pid);
	return (EXIT_SUCCESS);
}

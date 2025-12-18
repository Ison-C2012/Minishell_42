/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 20:34:18 by keitotak          #+#    #+#             */
/*   Updated: 2025/12/17 18:22:25 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static int	status_code(int status)
{
	int	code;

	if (WIFEXITED(status))
		code = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
		code = WTERMSIG(status) + 128;
	return (code);
}

int	wait_for_children(int *pidarr, int nbr)
{
	int	wstatus;
	int	res;
	int	i;

	i = 0;
	while (i < nbr)
	{
		if (i == nbr - 1)
			res = waitpid(pidarr[i], &wstatus, 0);
		else
			res = waitpid(pidarr[i], NULL, 0);
		if (res == error)
		{
			perror("waitpid");
			return (failure);
		}
		i++;
	}
	return (status_code(wstatus));
}

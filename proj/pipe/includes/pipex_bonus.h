/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keitotak <keitotak@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 14:58:59 by keitotak          #+#    #+#             */
/*   Updated: 2025/12/17 17:08:17 by keitotak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include "libft_bonus.h"
# include "ft_printf.h"

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>

# define STDIN 0
# define STDOUT 1
# define IN 0
# define OUT 1

typedef enum s_bool
{
	error = -1,
	success,
	failure
}	t_bool;

typedef struct s_pids
{
	pid_t	value;
	void	*next;
}	t_pids;

typedef struct s_pipex
{
	char	*infile;
	char	*outfile;
	int		p_fd[2];
	int		forkcnt;
	int		child_pnbr;
	t_list	*cmdlst;
	int		*pidarr;
}	t_pipex;

// process.c
int		fork_processes(t_pipex *p, char **ev, int n);

// exec.c
int		exec_command(char *cmd, char **ev);
char	*free_arrs_ret_s(char **arrs, char *s);

//wait.c
int		wait_for_children(int *pidarr, int nbr);

//helper.c
int		handle_noexist_cmd(char **cmdset);

#endif

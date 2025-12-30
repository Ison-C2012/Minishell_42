/*This function takes two arguments as two commands,
 * and redirect from left to right.*/

#include <unistd.h>
#include <stdio.h>

typedef struct s_cmd
{
	char	**leftset;
	char	**rightset;
}	t_cmd;

char	**create_cmdarr(char *cmdstr)
{
	char	**cmdarr;

	cmdarr = ft_split(cmdstr, ' ');
	return (cmdarr);
}

void	free_array(char **arr)
{
	char	**tmp;

	tmp = arr;
	while (*tmp)
		free(*tmp++);
	free(arr);
}

void	cleanup_exit(char *str, t_cmd *cmdset)
{
	perror(str);
	free_array(cmdset.leftset);
	free_array(cmdset.rightset);
	exit(EXIT_FAILURE);
}

int	execproc(t_cmd *cmdset, char **envp)
{

}

typedef struct 

char	*fork_processes()
{
	pid_t	procid[2];

	procid[0] = fork();
	if (procid[0] == -1)
		return ("fork");
	if (procid[0] == 0)
	{
		close(pipefd[0]);
		if (dup2(pipefd[1], STDOUT_FILENO) == -1)
		{
			close(pipefd[1]);
			cleanup_exit("dup2", cmdset);
		}
		execproc(cmdset, envp);
	}
	procid[1] = fork();
	if (procid[1] == -1)
		return ("fork");
	if (procid[1] == 0)
	{
		close(pipefd[1]);
		if (dup2(pipefd[0], STDIN_FILENO) == -1)
		{
			close(pipefd[0]);
			cleanup_exit("dup2", cmdset);
		}
		execproc(cmdset, envp);
	}
	return (NULL);
}

int	main(int argc, char **argv, char **envp)
{
	t_cmd	cmdset;
	int		pipefd[2];
	int		res;

	if (argc != 3)
		return (1);
	cmdset.leftset = create_cmdarr(argv[1]);
	cmdset.rightset = create_cmdarr(argv[2]);
	if (cmdset.leftset == NULL || cmdset.rightset == NULL)
		return (1);
	if (pipe(pipefd) == -1)
		cleanup_exit("pipe", cmdset);
	res = fork_processes(pipefd);
	close(pipefd[0]);
	close(pipefd[1]);
	if (res != NULL)
		cleanup_exit(res, cmdset);
	return (wait_for_children());
}

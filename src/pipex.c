/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 18:19:47 by alida-si          #+#    #+#             */
/*   Updated: 2022/04/13 01:25:44 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	check_cmd(t_pipex *p, int i)
{
	char	*aux;
	int		j;

	aux = ft_strjoin("/", p->cmds[i][0]);
	j = 0;
	while (p->env_list[j])
	{
		p->path = ft_strjoin(p->env_list[j], aux);
		if (access(p->path, F_OK) == 0)
		{
			free(aux);
			return(1);
		}
		free(p->path);
		j++;
	}
	free(aux);
	free_matrix(p->env_list);
	return(0);
}

int	get_comand(t_pipex *p)
{
	int	i;
	int	j;

	i = 2;
	j = 0;
	p->cmds = (char ***)malloc(((p->argc - 2) * sizeof(char **)));
	while (i < (p->argc - 1))
	{
		p->cmds[j] = ft_split(p->argv[i], ' ');
		i++;
		j++;
	}
	p->cmds[j] = NULL;
	return(1);
}

void	exec_child(t_pipex *p, char **cmd, int index)
{
	close(p->pipe_fd[0]);
	if (index == 0)
	{
		dup2(p->fdin, 0);
	}
	if (index == 1)
	{
		dup2(p->fdout, 1);
	}
	else
		dup2(p->pipe_fd[1], 1);
	close(p->pipe_fd[1]);
	execve(p->path, cmd, NULL);
}

int	teste(t_pipex *p)
{
	int i = 0;
	int pid;
	while (p->cmds[i])
	{
		check_cmd(p, i);
		pipe(p->pipe_fd);
		pid = fork();
		if (pid == 0)
			exec_child(p, p->cmds[i], i);
		waitpid(pid, NULL, 0);
		dup2(p->pipe_fd[0], 0);
		close(p->pipe_fd[0]);
		close(p->pipe_fd[1]);
		i++;
	}
	return(1);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	p;

	if (!check_args(argc, argv))
		return (1);
	init_struct(&p, argc, argv, envp);
	p.fdout = open(argv[argc - 1], O_WRONLY);
	p.fdin = open(argv[1], O_RDONLY);
	teste(&p);
	return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 18:19:47 by alida-si          #+#    #+#             */
/*   Updated: 2022/04/27 18:40:55 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	parent(t_pipex *p)
{
	dup2(p->pipe_fd[0], 0);
	close(p->pipe_fd[0]);
	close(p->pipe_fd[1]);
	close(p->fdin);
}

void	exec_child(t_pipex *p, char **cmd, int index)
{
	close(p->pipe_fd[0]);
	if (index == 0 && p->fdin < 0)
	{
		free_pipex(p);
		exit (EXIT_FAILURE);
	}
	if (index == 0)
	{
		dup2(p->fdin, 0);
		close_files(p);
	}
	if (index == 1)
	{
		dup2(p->fdout, 1);
		close_files(p);
	}
	else
		dup2(p->pipe_fd[1], 1);
	close(p->pipe_fd[1]);
	if (execve(p->path[index], cmd, NULL) == -1)
	{
		free_pipex(p);
		exit(0);
	}
}

void	check_cmd(t_pipex *p, int i)
{
	if (!valid_cmd(p, i))
	{
		write(2, p->cmds[i][0], ft_strlen(p->cmds[i][0]));
		write(2, ": command not found\n", 20);
		if ((p->path[0] == NULL))
			p->path[0] = ft_strdup(" ");
		if (i == 1)
		{
			free_pipex(p);
			exit(127);
		}
	}
}

int	fork_it(t_pipex *p)
{
	int	wstatus;
	int	i;
	int	pid;

	i = 0;
	while (p->cmds[i])
	{
		check_cmd(p, i);
		if (pipe(p->pipe_fd) == -1)
			return (error_msg("Pipe error\n"));
		pid = fork();
		if (pid < 0)
			return (error_msg("Fork error\n"));
		if (pid == 0)
			exec_child(p, p->cmds[i], i);
		parent(p);
		i++;
	}
	waitpid(pid, &p->status, 0);
	if (WIFEXITED(p->status))
		wstatus = WEXITSTATUS(p->status);
	return (wstatus);
}

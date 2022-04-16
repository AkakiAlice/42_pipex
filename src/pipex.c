/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 18:19:47 by alida-si          #+#    #+#             */
/*   Updated: 2022/04/16 20:47:04 by alida-si         ###   ########.fr       */
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
			return (1);
		}
		free(p->path);
		j++;
	}
	free(aux);
	free_matrix(p->env_list);
	return (0);
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
	return (1);
}

void	exec_child(t_pipex *p, char **cmd, int index)
{
	close(p->pipe_fd[0]);
	if (index == 0)
	{
		dup2(p->fdin, 0);
		close(p->fdin);
		close(p->fdout);
	}
	if (index == 1)
	{
		dup2(p->fdout, 1);
		close(p->fdin);
		close(p->fdout);
	}
	else
		dup2(p->pipe_fd[1], 1);
	close(p->pipe_fd[1]);
	if (execve(p->path, cmd, NULL) == -1)
	{
		error_msg("Error execve\n");
		exit(0);
	}
}

void	parent(t_pipex *p)
{
	dup2(p->pipe_fd[0], 0);
	close(p->pipe_fd[0]);
	close(p->pipe_fd[1]);
	close(p->fdin);
	free(p->path);
}

int	teste(t_pipex *p)
{
	int	i;
	int	pid;

	i = 0;
	while (p->cmds[i])
	{
		if (!check_cmd(p, i))
			return (error_msg("Invalid comand\n"));
		if (pipe(p->pipe_fd) == -1)
			return (error_msg("Pipe error\n"));
		pid = fork();
		if (pid < 0)
			return (error_msg("Fork error\n"));
		if (pid == 0)
			exec_child(p, p->cmds[i], i);
		waitpid(pid, NULL, 0);
		parent(p);
		i++;
	}
	return (1);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	p;

	if (argc == 5)
	{
		if (!open_files(argc, argv, &p))
			return (1);
		init_struct(&p, argc, argv, envp);
		if (!teste(&p))
		{
			free_cmds(&p);
			return (1);
		}
		close(p.fdout);
		free_matrix(p.env_list);
		free_cmds(&p);
		return (0);
	}
	error_msg("Invalid number of arguments\n");
	return (1);
}

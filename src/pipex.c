/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 18:19:47 by alida-si          #+#    #+#             */
/*   Updated: 2022/04/26 20:44:19 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	check_cmd(t_pipex *p, int i)
{
	//char	*aux;
	int		j;
	/*if (i == 1 && p->path != NULL)
		free(p->path);*/
	p->aux = ft_strjoin("/", p->cmds[i][0]);
	j = 0;
	while (p->env_list[j])
	{
		p->path[i] = ft_strjoin(p->env_list[j], p->aux);
		if (access(p->path[i], F_OK) == 0)
		{
			free(p->aux);
			return (1);
		}
		free(p->path[i]);
		p->path[i] = NULL;
		j++;
	}
	if (p->aux != NULL)
		free(p->aux);
	/*if (p->env_list != NULL)
		free_matrix(p->env_list);*/
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
		p->cmds[j] = ft_split2(p->argv[i], ' ');
		i++;
		j++;
	}
	p->cmds[j] = NULL;
	return (1);
}

void	exec_child(t_pipex *p, char **cmd, int index)
{
	//ft_printf("%s\n", p->cmds[0][0]);
	//ft_printf("--%s--\n", p->path[0]);
	if ((p->path[0] == NULL))
		p->path[0] = "/bin/";
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
	if (execve(p->path[index], cmd, NULL) == -1)
	{
		free_cmds(p);
		free_matrix(p->env_list);
		free(p->path);
	//	free_matrix(p->path);
		exit(0);
	}
}

void	parent(t_pipex *p)
{
	dup2(p->pipe_fd[0], 0);
	close(p->pipe_fd[0]);
	close(p->pipe_fd[1]);
	close(p->fdin);
	/*if (p->path != NULL)
		free(p->path);*/
}

int	teste(t_pipex *p)
{
	int	wstatus;
	int	i;
	int	pid;

	i = 0;
	while (p->cmds[i])
	{
		if (!check_cmd(p, i))
		{
			write(2, p->cmds[i][0], ft_strlen(p->cmds[i][0]));
			write(2, ": command not found\n", 20);
			if (i == 1)
			{
				if (p->path[0] != NULL)
				{
					free(p->path[0]);
					//p->path[0] = NULL;
				}
				free(p->path);
				//p->path = NULL;
				//p->path = NULL;
				free_matrix(p->env_list);
				free_cmds(p);
				exit(127);
			}
		}
		if (pipe(p->pipe_fd) == -1)
			return (error_msg("Pipe error\n"));
		pid = fork();
		if (pid < 0)
			return (error_msg("Fork error\n"));
		if (pid == 0)
			exec_child(p, p->cmds[i], i);
		waitpid(pid, &p->status, 0);
		if (WIFEXITED(p->status))
			wstatus = WEXITSTATUS(p->status);
		parent(p);
		i++;
	}
	return (wstatus);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	p;
	int t;

	if (argc == 5)
	{
		open_files(argc, argv, &p);
		init_struct(&p, argc, argv, envp);
		t = teste(&p);
		if (t != 0)
		{
			free_matrix(p.path);
			free_cmds(&p);
			return (t);
		}
		close(p.fdout);
		free_matrix(p.env_list);
		free_cmds(&p);
		//ft_printf("%s\n", p.path[1]);
		if (p.path[1] != NULL && p.path[0] == NULL)
			free(p.path[1]);
		free_matrix(p.path);
		p.path = NULL;
		//ft_printf("-%s-\n", p.path);
		return (0);
	}
	error_msg("Invalid number of arguments\n");
	return (1);
}

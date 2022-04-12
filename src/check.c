/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 02:01:22 by alida-si          #+#    #+#             */
/*   Updated: 2022/04/06 23:53:20 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	check_args(int argc, char *argv[])
{
	int	fd;

	if (argc != 5)
		return (error_msg("Invalid number of arguments\n"));
	if (access(argv[1], R_OK) == -1)
		return (error_msg("Can't open infile\n"));
	if (access(argv[argc - 1], W_OK) == -1)
	{
		fd = open(argv[argc - 1], O_CREAT, 0777);
		if (fd == -1)
		{
			close(fd);
			return (error_msg("Can't creat outfile\n"));
		}
	}
	return (1);
}

void	get_path(t_pipex *p)
{
	int		i;
	char	*aux;

	i = 0;
	while(p->envp[i])
	{
		if(ft_strncmp("PATH", p->envp[i], 4) == 0)
			aux = p->envp[i];
		i++;
	}
	p->path_list = ft_split(aux, ':');
}

int	check_cmd(t_pipex *p)
{
	char	**cmd_token;
	char	*aux;
	char	*path;
	int		i;
	int		j;
	int		check;

	i = 1;
	while (++i < (p->argc - 1))
	{
		cmd_token = ft_split(p->argv[i], ' ');
		aux = ft_strjoin("/", cmd_token[0]);
		j = 0;
		check = 0;
		while (p->path_list[j])
		{
			path = ft_strjoin(p->path_list[j], aux);
			if (access(path, F_OK) == 0)
				check++;
			free(path);
			j++;
		}
		free_matrix(cmd_token);
		free(aux);
		if (check == 0)
		{
			free_matrix(p->path_list);
			return(error_msg("Invalid comand\n"));
		}
	}
	free_matrix(p->path_list);
	return (1);
}


void	init_struct(t_pipex *p, int argc, char *argv[], char *envp[])
{
	p->argv = argv;
	p->envp = envp;
	p->argc = argc;
	p->infile = argv[1];
	p->outfile = argv[argc];
	get_path(p);
}
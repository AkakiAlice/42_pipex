/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 02:01:22 by alida-si          #+#    #+#             */
/*   Updated: 2022/04/14 03:59:44 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	open_files(int argc, char *argv[], t_pipex *p)
{
	if (access(argv[1], R_OK) == -1)
		return (error_msg("Can't open infile\n"));
	if (access(argv[argc - 1], W_OK) == -1)
	{
		p->fdout = open(argv[argc - 1], O_CREAT, 0777);
		if (p->fdout == -1)
		{
			close(p->fdout);
			return (error_msg("Can't creat outfile\n"));
		}
	}
	p->fdout = open(argv[argc - 1], O_WRONLY);
	p->fdin = open(argv[1], O_RDONLY);
	return (1);
}

void	get_path(t_pipex *p)
{
	int		i;
	char	*aux;

	i = 0;
	while (p->envp[i])
	{
		if (ft_strncmp("PATH", p->envp[i], 4) == 0)
			aux = p->envp[i];
		i++;
	}
	p->env_list = ft_split(aux, ':');
}

void	init_struct(t_pipex *p, int argc, char *argv[], char *envp[])
{
	p->argv = argv;
	p->envp = envp;
	p->argc = argc;
	p->infile = argv[1];
	p->outfile = argv[argc];
	p->path = NULL;
	get_path(p);
	get_comand(p);
}

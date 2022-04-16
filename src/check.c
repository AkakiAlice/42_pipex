/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 02:01:22 by alida-si          #+#    #+#             */
/*   Updated: 2022/04/16 04:37:23 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	open_files(int argc, char *argv[], t_pipex *p)
{
	if (access(argv[1], R_OK) == -1)
		return (error_msg("Can't open infile\n"));
	p->fdout = open(argv[argc - 1], O_RDWR | O_CREAT | O_TRUNC, 0777);
	p->fdin = open(argv[1], O_RDONLY);
	if (p->fdout == -1 || p->fdin == -1)
	{
		close(p->fdout);
		close(p->fdout);
		return (error_msg("Error in open files\n"));
	}
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 02:08:00 by alida-si          #+#    #+#             */
/*   Updated: 2022/04/27 18:44:59 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	valid_cmd(t_pipex *p, int i)
{
	int		j;

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

int	error_msg(char *error_str)
{
	write(2, error_str, ft_strlen(error_str));
	return (0);
}

void	close_files(t_pipex *p)
{
	close(p->fdin);
	close(p->fdout);
}

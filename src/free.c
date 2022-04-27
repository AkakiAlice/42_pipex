/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 17:51:46 by alida-si          #+#    #+#             */
/*   Updated: 2022/04/27 17:54:39 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_pipex(t_pipex *p)
{
	free_matrix(p->env_list);
	free_cmds(p);
	free_path(p);
}

void	free_path(t_pipex *p)
{
	int	i;

	i = 0;
	while (i < (p->argc - 3))
	{
		if (p->path[i] != NULL)
		{
			free(p->path[i]);
			p->path[i] = NULL;
		}
		i++;
	}
	free(p->path);
}

void	free_cmds(t_pipex *p)
{
	int	i;

	if (p->cmds)
	{
		i = 0;
		while (p->cmds[i])
		{
			free_matrix(p->cmds[i]);
			i++;
		}
		free(p->cmds);
	}
}

void	free_matrix(char **ptr)
{
	int	i;

	if (ptr != NULL)
	{
		i = 0;
		while (ptr[i])
		{
			free(ptr[i]);
			ptr[i] = NULL;
			i++;
		}
		free(ptr);
	}
}

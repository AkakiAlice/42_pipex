/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 02:08:00 by alida-si          #+#    #+#             */
/*   Updated: 2022/04/26 00:49:25 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

int	error_msg(char *error_str)
{
	write(2, error_str, ft_strlen(error_str));
	return (0);
}

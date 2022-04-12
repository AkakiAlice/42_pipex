/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 18:19:47 by alida-si          #+#    #+#             */
/*   Updated: 2022/04/12 16:53:40 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*void	test(t_pipex p)
{
	char	**cmd;

	cmd = ft_split(p.argv[2], ' ');
	execve(path, cmd, NULL);
	ft_printf("%s\n", cmd[0]);
}*/

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	p;

	if (!check_args(argc, argv))
		return (1);
	init_struct(&p, argc, argv, envp);
	if (!check_cmd(&p))
		return (1);
	test(p);
	return (0);
}
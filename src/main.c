/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 18:19:30 by alida-si          #+#    #+#             */
/*   Updated: 2022/04/27 18:45:08 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_struct(t_pipex *p, int argc, char *argv[], char *envp[])
{
	p->argv = argv;
	p->envp = envp;
	p->argc = argc;
	p->path = (char **)malloc(((sizeof(char *)) * (2 + 1)));
	p->path[2] = NULL;
	get_path(p);
	get_comand(p);
}

void	open_files(int argc, char *argv[], t_pipex *p)
{
	p->fdin = open(argv[1], O_RDONLY);
	if (p->fdin < 0)
		perror(argv[1]);
	p->fdout = open(argv[argc - 1], O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (p->fdout < 0)
	{
		close_files(p);
		perror(argv[argc - 1]);
		exit(EXIT_FAILURE);
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	p;
	int		t;

	if (argc == 5)
	{
		open_files(argc, argv, &p);
		init_struct(&p, argc, argv, envp);
		t = fork_it(&p);
		free_pipex(&p);
		return (t);
	}
	error_msg("Invalid number of arguments\n");
	return (1);
}

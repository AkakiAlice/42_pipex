/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 18:20:27 by alida-si          #+#    #+#             */
/*   Updated: 2022/04/25 21:53:24 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include ".././libft/libft.h"
# include <sys/wait.h>
# include <errno.h>
# include <stdio.h>

typedef struct s_pipex
{
	char	**env_list;
	char	**path;
	char	**argv;
	char	**envp;
	int		argc;
	char	*infile;
	char	*outfile;
	char	***cmds;
	int		pipe_fd[2];
	int		status;
	int		fdin;
	int		fdout;
	char	*aux;
}			t_pipex;

int		check_args(int argc, char *argv[]);
void	get_path(t_pipex *p);
int		check_cmd(t_pipex *p, int i);
void	init_struct(t_pipex *p, int argc, char *argv[], char *envp[]);
void	free_matrix(char **ptr);
void	free_cmds(t_pipex *p);
int		error_msg(char *error_str);
int		get_comand(t_pipex *p);
void	open_files(int argc, char *argv[], t_pipex *p);

#endif
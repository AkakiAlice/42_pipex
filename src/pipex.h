/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alida-si <alida-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 18:20:27 by alida-si          #+#    #+#             */
/*   Updated: 2022/04/12 16:50:09 by alida-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include ".././libft/libft.h"

typedef struct s_pipex
{
	char	**path_list;
	char	*path;
	char	**argv;
	char	**envp;
	int		argc;
	char	*infile;
	char	*outfile;
}			t_pipex;

int		check_args(int argc, char *argv[]);
void	get_path(t_pipex *p);
int		check_cmd(t_pipex *p);
void	init_struct(t_pipex *p, int argc, char *argv[], char *envp[]);
void	free_matrix(char **ptr);
int		error_msg(char *error_str);

#endif
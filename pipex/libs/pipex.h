/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcuevas- <lcuevas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:49:46 by lcuevas-          #+#    #+#             */
/*   Updated: 2024/03/06 19:44:20 by lcuevas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

/*---------------------------------   LIBS   ---------------------------------*/
# include "libft/libft.h"
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>

/*--------------------------------   MACROS   --------------------------------*/
/*INTS*/
# define INT_MAX 2147483647
# define INT_MIN -2147483648

/*--------------------------------   STRUCTS   -------------------------------*/

typedef struct s_pipex
{
	int		infile;
	int		outfile;
	int		pipe[2];
	pid_t	pid1;
	pid_t	pid2;
	char	*command_path;
	char	**path;
	char	**command_argument;

}	t_pipex;

/*-------------------------------   FUNCTIONS   ------------------------------*/

//de momento tengo un caso marginal cuando la lusta es par
//justo la primera acciom negativa cuesta lo mimsmo en positivo que en negativo

// main file
int		main(int argc, char **argv, char **envp);
void	ft_path(t_pipex *p, char **envp);
void	ft_pipex(t_pipex *p, char **argv, char **envp);
void	ft_child(t_pipex *p, char **envp, char *argv_cmd);
void	ft_parent(t_pipex *p, char **envp, char *argv_cmd2);

// utils file
void	ft_open_file(t_pipex *p, char **argv);
int		ft_command_filter(t_pipex *p, char *cmd);
void	ft_liberator(t_pipex *p);
void	ft_error(void);

#endif

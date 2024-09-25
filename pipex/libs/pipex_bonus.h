/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcuevas- <lcuevas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:49:46 by lcuevas-          #+#    #+#             */
/*   Updated: 2024/03/08 18:27:53 by lcuevas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

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
	pid_t	pid;
	int		i;
	int		infile;
	int		outfile;
	int		pipe[2];
	char	*command_path;
	char	**path;
	char	**command_argument;

}	t_pipex;

/*-------------------------------   FUNCTIONS   ------------------------------*/

// main file
int		main(int argc, char **argv, char **envp);
void	ft_path(t_pipex *p, char **envp);
void	ft_pipex_bonus(t_pipex *p, int argc, char **argv, char **envp);
void	ft_parent(t_pipex *p);
void	ft_last_command(t_pipex *p, char **envp, char *last_cmd);

// utils file
void	ft_open_file(t_pipex *p, int argc, char **argv);
int		ft_command_filter(t_pipex *p, char *cmd);
void	ft_liberator(t_pipex *p);
void	ft_error(void);
void	ft_here_doc(t_pipex *p, char *limiter);

#endif

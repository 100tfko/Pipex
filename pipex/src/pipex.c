/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcuevas- <lcuevas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 15:04:34 by lcuevas-          #+#    #+#             */
/*   Updated: 2024/03/06 19:45:02 by lcuevas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/pipex.h"

void	ft_parent(t_pipex *p, char **envp, char *argv_cmd2)
{
	if (ft_command_filter(p, argv_cmd2) == 1)
		ft_error();
	close (p->pipe[1]);
	if (dup2(p->pipe[0], STDIN_FILENO) == -1)
		ft_error();
	if (dup2(p->outfile, STDOUT_FILENO) == -1)
		ft_error();
	close (p->pipe[0]);
	close (p->outfile);
	if (execve(p->command_path, p->command_argument, envp) == -1)
		ft_error();
}

void	ft_child(t_pipex *p, char **envp, char *argv_cmd)
{
	if (ft_command_filter(p, argv_cmd) == 1)
		ft_error();
	close (p->pipe[0]);
	if (dup2(p->infile, STDIN_FILENO) == -1)
		ft_error();
	if (dup2(p->pipe[1], STDOUT_FILENO) == -1)
		ft_error();
	close (p->pipe[1]);
	close (p->infile);
	if (execve(p->command_path, p->command_argument, envp) == -1)
		ft_error();
}

void	ft_pipex(t_pipex *p, char **argv, char **envp)
{
	if (access(argv[1], R_OK == -1) || access(argv[4], W_OK == -1))
		ft_error();
	pipe(p->pipe);
	p->pid1 = fork();
	if (p->pid1 == -1)
		ft_error();
	if (p->pid1 == 0)
		ft_child(p, envp, argv[2]);
	waitpid(p->pid1, NULL, WNOHANG);
	p->pid2 = fork();
	if (p->pid2 == -1)
		ft_error();
	if (p->pid2 == 0)
		ft_parent(p, envp, argv[3]);
	waitpid(p->pid2, NULL, WNOHANG);
}

void	ft_path(t_pipex *p, char **envp)
{
	char	*envp_path;
	int		i;

	i = 0;
	envp_path = 0;
	while (envp[i])
	{
		if (strncmp(envp[i], "PATH=", 5) == 0)
		{
			envp_path = envp[i] + 5;
			break ;
		}
		i++;
	}
	if (!envp_path)
		ft_error();
	p->path = ft_split (envp_path, ':');
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	*p;

	if (argc != 5)
		exit(1);
	else
	{
		p = malloc(sizeof(t_pipex));
		ft_open_file(p, argv);
		ft_path(p, envp);
		ft_pipex(p, argv, envp);
		ft_liberator(p);
	}
}

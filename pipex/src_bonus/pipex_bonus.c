/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcuevas- <lcuevas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 15:04:34 by lcuevas-          #+#    #+#             */
/*   Updated: 2024/03/08 18:04:30 by lcuevas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/pipex_bonus.h"

void	ft_parent(t_pipex *p)
{
	waitpid(p->pid, NULL, WNOHANG);
	close (p->pipe[1]);
	if (dup2(p->pipe[0], STDIN_FILENO) == -1)
		ft_error();
}

void	ft_last_command(t_pipex *p, char **envp, char *last_cmd)
{
	p->pid = fork();
	if (p->pid == -1)
		ft_error();
	if (p->pid == 0)
	{
		if (ft_command_filter(p, last_cmd) == 1)
			ft_error();
		close (p->pipe[0]);
		if (dup2(p->outfile, STDOUT_FILENO) == -1)
			ft_error();
		if (execve(p->command_path, p->command_argument, envp) == -1)
			ft_error();
	}
}

void	ft_pipex_bonus(t_pipex *p, int argc, char **argv, char **envp)
{
	while (p->i < argc -2)
	{
		pipe(p->pipe);
		p->pid = fork();
		if (p->pid == -1)
			ft_error();
		if (p->pid == 0)
		{
			if (ft_command_filter(p, argv[p->i]) == 1)
				ft_error();
			close (p->pipe[0]);
			if (dup2(p->pipe[1], STDOUT_FILENO) == -1)
				ft_error();
			if (execve(p->command_path, p->command_argument, envp) == -1)
				ft_error();
		}
		else
			ft_parent(p);
		p->i += 1;
	}
	ft_last_command(p, envp, argv[argc -2]);
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

	if (argc < 5)
		return (0);
	else
	{
		p = malloc(sizeof(t_pipex));
		ft_open_file(p, argc, argv);
		ft_path(p, envp);
		ft_pipex_bonus(p, argc, argv, envp);
		ft_liberator(p);
	}
}

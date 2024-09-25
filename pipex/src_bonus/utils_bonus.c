/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcuevas- <lcuevas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 18:24:24 by lcuevas-          #+#    #+#             */
/*   Updated: 2024/03/08 18:30:25 by lcuevas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/pipex_bonus.h"

void	ft_here_doc(t_pipex *p, char *limiter)
{
	char	*line;

	pipe(p->pipe);
	while (1)
	{
		line = get_next_line(0);
		if (ft_strncmp(line, limiter, ft_strlen(limiter) + 1) == 10)
		{
			free (line);
			break ;
		}
		write (p->pipe[1], line, ft_strlen(line));
		free (line);
	}
	close (p->pipe[1]);
}

void	ft_error(void)
{
	perror("Error\n");
	exit(1);
}

void	ft_liberator(t_pipex *p)
{
	int	i;

	i = 0;
	free(p->command_path);
	while (p->path[i])
	{
		free(p->path[i]);
		i += 1;
	}
	free(p->path);
	i = 0;
	free(p->command_argument);
	free(p);
}

int	ft_command_filter(t_pipex *p, char *cmd)
{
	int		i;
	char	*cmd_slash;
	char	*tmp;

	i = 0;
	p->command_argument = ft_split(cmd, ' ');
	cmd_slash = ft_strjoin("/", p->command_argument[0]);
	while (p->path[i])
	{
		p->command_path = ft_strjoin(p->path[i], cmd_slash);
		tmp = p->command_path;
		if (access(p->command_path, X_OK) == 0)
			return (0);
		free(tmp);
		i += 1;
	}
	return (1);
}

void	ft_open_file(t_pipex *p, int argc, char **argv)
{
	if (ft_strncmp(argv[1], "here_doc", 9) == 0)
	{
		ft_here_doc(p, argv[2]);
		if (dup2(p->pipe[0], STDIN_FILENO) == -1)
			ft_error();
		close (p->pipe[0]);
		p->i = 3;
	}
	else
	{
		p->infile = open(argv[1], O_RDONLY, 00444);
		if (p->infile == -1)
			ft_error();
		if (dup2(p->infile, STDIN_FILENO) == -1)
			ft_error();
		close (p->infile);
		p->i = 2;
	}
	p->outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 00644);
}

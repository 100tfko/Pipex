/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcuevas- <lcuevas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 18:24:24 by lcuevas-          #+#    #+#             */
/*   Updated: 2024/03/08 17:38:13 by lcuevas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/pipex.h"

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

void	ft_open_file(t_pipex *p, char **argv)
{
	p->infile = open(argv[1], O_RDONLY, 00444);
	if (p->infile == -1)
		ft_error();
	p->outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 00644);
}

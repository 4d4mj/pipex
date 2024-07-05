/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabado <ajabado@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 21:56:58 by ajabado           #+#    #+#             */
/*   Updated: 2024/07/03 21:56:58 by ajabado          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static void	ft_write_to_pipe(int *fd, char **argv)
{
	char	*line;
	char	*limiter;

	limiter = argv[2];
	write(STDIN, "pipex: here_doc> ", 17);
	line = get_next_line(STDIN);
	while (line)
	{
		if (!ft_strcmp(limiter, line))
			break ;
		write(*fd, line, ft_strlen(line));
		free(line);
		write(STDIN, "pipex: here_doc> ", 17);
		line = get_next_line(STDIN);
	}
	free(line);
	close(*fd);
	exit(6);
}

int	ft_here_doc(char **argv)
{
	int	fd[2];
	int	pid;

	if (pipe(fd) == -1)
		ft_error(3, NULL);
	pid = fork();
	if (pid == -1)
		ft_error(4, NULL);
	if (pid)
	{
		waitpid(pid, NULL, 0);
		close(fd[1]);
		dup2(fd[0], 0);
		close(fd[0]);
	}
	else
	{
		close(fd[0]);
		ft_write_to_pipe(&fd[1], argv);
	}
	return (STDIN);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabado <ajabado@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 21:55:25 by ajabado           #+#    #+#             */
/*   Updated: 2024/07/03 21:55:25 by ajabado          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int ft_open_file(char *file_path, int mode)
{
	int fd;

	if (mode == IN) {
		if (access(file_path, F_OK))
			ft_error(0, file_path);
		fd = open(file_path, O_RDONLY);
	} else if (mode == OUTWRITE) {
		fd = open(file_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	} else {
		fd = open(file_path, O_WRONLY | O_CREAT | O_APPEND, 0644);
	}

	if (fd == -1)
		ft_error(2, file_path);

	return fd;
}

static int	ft_init(int argc, char **argv, int *fd_in, int *fd_out)
{
	int	i;

	if (!ft_strcmp(argv[1], "here_doc"))
	{
		i = 3;
		*fd_in = ft_here_doc(argv);
		*fd_out = ft_open_file(argv[argc - 1], OUTAPPEND);
	}
	else
	{
		i = 1;
		*fd_in = ft_open_file(argv[i++], IN);
		*fd_out = ft_open_file(argv[argc - 1], OUTWRITE);
	}
	return (i);
}

static void	ft_new_command(char *command, char **envp)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
		ft_error(3, NULL);
	pid = fork();
	if (pid == -1)
		ft_error(4, NULL);
	if (pid)
	{
		close(fd[1]);
		dup2(fd[0], STDIN);
		waitpid(-1, NULL, WNOHANG);
	}
	else
	{
		close(fd[0]);
		dup2(fd[1], STDOUT);
		ft_execute(command, envp);
	}
}

int	main(int argc, char **argv, char **envp)
{
	int	fd_in;
	int	fd_out;
	int	i;

	if (argc < 5 || (!ft_strcmp(argv[1], "here_doc") && argc < 6))
		ft_error(1, NULL);
	else
	{
		i = ft_init(argc, argv, &fd_in, &fd_out);
		dup2(fd_in, STDIN);
		dup2(fd_out, STDOUT);
		ft_new_command(argv[i++], envp);
		while (i < argc - 2)
			ft_new_command(argv[i++], envp);
		ft_execute(argv[i], envp);
	}
	return (0);
}

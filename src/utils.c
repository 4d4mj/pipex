/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabado <ajabado@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 21:56:40 by ajabado           #+#    #+#             */
/*   Updated: 2024/07/03 21:56:40 by ajabado          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_error(int exit_code, char *name)
{
	if (exit_code == 1)
		write(STDERR, ERR_ARG, ft_strlen(ERR_ARG));
	else if (exit_code == 2)
	{
		write(STDERR, name, ft_strlen(name));
		write(STDERR, ERR_FILE, ft_strlen(ERR_FILE));
	}
	else if (exit_code == 3)
		write(STDERR, ERR_PIPE, ft_strlen(ERR_PIPE));
	else if (exit_code == 4)
		write(STDERR, ERR_FORK, ft_strlen(ERR_FORK));
	else if (exit_code == 127)
	{
		write(STDERR, name, ft_strlen(name));
		write(STDERR, ERR_CMD, ft_strlen(ERR_CMD));
	}
	exit(exit_code);
}

char	*ft_get_command_path(char *command_name, char **envp)
{
	char	*path;
	char	*directory;
	char	*bin;
	int		i;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5))
		i++;
	if (!envp[i])
		return (ft_strdup(command_name));
	path = &envp[i][5];
	while (path && ft_strichr(path, ':') != -1)
	{
		directory = ft_strndup(path, ft_strichr(path, ':'));
		bin = ft_join_path(directory, command_name);
		free(directory);
		if (access(bin, F_OK | X_OK) == 0)
			return (bin);
		free(bin);
		path += ft_strichr(path, ':') + 1;
	}
	return (ft_strdup(command_name));
}

void	ft_execute(char *command, char **envp)
{
	char	**cmd_args;
	char	*cmd_path;
	int		i;

	cmd_args = ft_split_command(command, ' ');
	if (ft_strchr (*cmd_args, '/'))
		cmd_path = *cmd_args;
	else
		cmd_path = ft_get_command_path(cmd_args[0], envp);
	execve(cmd_path, cmd_args, envp);
	i = 0;
	while (cmd_args[i])
		free(cmd_args[i++]);
	free(cmd_args);
	free(cmd_path);
	ft_error(127, command);
}

int	ft_strichr(const char *s, int c)
{
	int		i;
	char	ch;

	ch = (unsigned char)c;
	i = 0;
	while (s[i])
	{
		if (s[i] == ch)
			return (i);
		i++;
	}
	if (!ch)
		return (i);
	return (-1);
}

char	*ft_join_path(char *directory, char *command)
{
	char	*full_path;
	int		i;
	int		j;

	full_path = malloc((ft_strlen(directory) + ft_strlen(command) + 2) * \
		sizeof(char));
	if (!full_path)
		return (NULL);
	i = 0;
	j = 0;
	while (directory[j])
		full_path[i++] = directory[j++];
	full_path[i++] = '/';
	j = 0;
	while (command[j])
		full_path[i++] = command[j++];
	full_path[i] = '\0';
	return (full_path);
}

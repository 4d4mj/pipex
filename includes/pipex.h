/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabado <ajabado@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 15:00:51 by ajabado           #+#    #+#             */
/*   Updated: 2024/07/03 15:00:51 by ajabado          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/includes/libft.h"

# include <unistd.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>

# define STDIN		0
# define STDOUT		1
# define STDERR		2

enum	e_mode
{
	IN,
	OUTWRITE,
	OUTAPPEND
};

# define ERR_ARG	"Wrong usage. Invalid number of arguments.\n"
# define ERR_FILE	": No such file or directory\n"
# define ERR_PIPE	"Error on initializing pipe.\n"
# define ERR_FORK	"Error on forking.\n"
# define ERR_CMD	": command not found\n"

int		ft_open_file(char *file_path, int mode);
char	**ft_split_command(char const *s, char c);
char	*ft_get_command_path(char *command_name, char **envp);
int		ft_here_doc(char **argv);
void	ft_error(int exit_code, char *name);
int		ft_strichr(const char *s, int c);
char	*ft_join_path(char *directory, char *command);
void	ft_execute(char *command, char **envp);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajabado <ajabado@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 21:56:50 by ajabado           #+#    #+#             */
/*   Updated: 2024/07/03 21:56:50 by ajabado          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static int	ft_within_quotes(const char *s, int pos)
{
	int		i;
	int		before;
	int		after;

	i = 0;
	before = -1;
	after = -1;
	while (s[i])
	{
		if ((s[i] == '\"' || s[i] == '\'') && before == -1)
			before = i;
		else if (s[i] == s[before] && after == -1)
		{
			after = i;
			if (pos > before && pos < after)
				return (1);
			before = -1;
			after = -1;
		}
		i++;
	}
	return (0);
}

static size_t	ft_append(char **res, const char *prev, size_t size, char c)
{
	if (*prev == c)
	{
		prev++;
		size--;
	}
	if ((*prev == '\"' || *prev == '\'') && (*(prev + size - 1)) == *prev)
	{
		prev++;
		size -= 2;
	}
	*res = (char *)malloc((size + 1) * sizeof(char));
	ft_strlcpy(*res, prev, size + 1);
	return (1);
}

static void	ft_create_command(char **result, char const *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	size;
	size_t	prev;
	size_t	next;

	i = 0;
	j = 0;
	prev = i;
	next = i;
	while (1)
	{
		if ((s[i] == c || !(s[i])) && !ft_within_quotes(s, i))
			next = i;
		size = next - prev;
		if (size > 1 || (size == 1 && s[i - 1] != c))
			j += ft_append(&result[j], &s[prev], size, c);
		if (!(s[i]))
			break ;
		prev = next;
		i++;
	}
	result[j] = NULL;
}

static size_t	count_commands(const char *s, char c)
{
	size_t	i;
	size_t	prev;
	size_t	next;
	size_t	size;
	size_t	counter;

	i = 0;
	prev = i;
	next = i;
	counter = 0;
	while (1)
	{
		if ((s[i] == c || !(s[i])) && !ft_within_quotes(s, i))
			next = i;
		size = next - prev;
		if (size > 1 || (size == 1 && s[i - 1] != c))
			counter++;
		if (!(s[i]))
			break ;
		prev = next;
		i++;
	}
	return (counter);
}

char	**ft_split_command(char const *s, char c)
{
	char	**res;

	if (!s)
		return (NULL);
	res = (char **)malloc((count_commands(s, c) + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	ft_create_command(res, s, c);
	return (res);
}

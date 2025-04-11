/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera@student.42madrid.com <brivera>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 18:48:25 by brivera@stu       #+#    #+#             */
/*   Updated: 2025/04/11 19:35:19 by brivera@stu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Nueva función: Salta hasta encontrar un pipe NO entre comillas
static size_t	skip_pipe_word(const char *s, size_t i)
{
	int	flag_single;
	int	flag_double;

	flag_single = 0;
	flag_double = 0;
	while (s[i])
	{
		flag_single = toggle_simples(s[i], flag_single, flag_double);
		flag_double = toggle_doubles(s[i], flag_single, flag_double);
		if (!flag_single && !flag_double && s[i] == '|')
			break ;
		i++;
	}
	return (i);
}

// cuenta palabras separadas por pipes (no por espacios)
static size_t	ft_count_pipe_words(const char *s)
{
	size_t	count;
	size_t	i;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && ft_isspace(s[i]))
			i++;
		if (!s[i] || s[i] == '|')
		{
			i++;
			continue ;
		}
		count++;
		i = skip_pipe_word(s, i);
	}
	return (count);
}

// Modificada: Rellena el array, dividiendo por pipes (no por espacios)
static char	**ft_fill_pipe_strs(char const *s, char **strs)
{
	size_t	i;
	size_t	j;
	size_t	start;
	size_t	end;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] && ft_isspace(s[i]))
			i++;
		if (!s[i])
			break ;
		start = i;
		end = skip_pipe_word(s, i);
		strs[j] = ft_strtrim_spaces(ft_substr(s, start, end - start));
		if (!strs[j])
			return (free_array(strs));
		j++;
		i = end;
		if (s[i] == '|')
			i++;
	}
	strs[j] = NULL;
	return (strs);
}

// Divide por pipes, respetando comillas
char	**ft_split_pipes(char const *s)
{
	size_t	word_count;
	char	**strs;

	if (!s)
		return (NULL);
	word_count = ft_count_pipe_words(s);
	strs = (char **)ft_calloc((word_count + 1), sizeof(char *));
	if (!strs)
		return (NULL);
	if (word_count == 0)
	{
		strs[0] = NULL;
		return (strs);
	}
	strs = ft_fill_pipe_strs(s, strs);
	return (strs);
}
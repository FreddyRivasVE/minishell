/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera@student.42madrid.com <brivera>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 12:07:42 by brivera@stu       #+#    #+#             */
/*   Updated: 2025/04/11 12:11:00 by brivera@stu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	skip_word(const char *s, size_t i)
{
	int	flag_single;
	int	flag_double;

	flag_single = 0;
	flag_double = 0;
	while (s[i])
	{
		flag_single = toggle_simples(s[i], flag_single, flag_double);
		flag_double = toggle_doubles(s[i], flag_single, flag_double);
		if (!flag_single && !flag_double && ft_isspace(s[i]))
			break ;
		i++;
	}
	return (i);
}

static size_t	ft_count_words(const char *s)
{
	size_t	count;
	size_t	i;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && ft_isspace(s[i]))
			i++;
		if (!s[i])
			break ;
		count++;
		i = skip_word(s, i);
	}
	return (count);
}

static char	**ft_free_strs(char **strs, size_t j)
{
	while (j > 0)
	{
		free(strs[j - 1]);
		j--;
	}
	free(strs);
	return (NULL);
}

static char	**ft_fill_strs(char const *s, char **strs)
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
		end = skip_word(s, i);
		strs[j] = ft_substr(s, start, end - start);
		if (!strs[j])
			return (ft_free_strs(strs, j));
		j++;
		i = end;
	}
	strs[j] = NULL;
	return (strs);
}

char	**ft_split_quotes(char const *s)
{
	size_t	word_count;
	char	**strs;

	if (!s)
		return (NULL);
	word_count = ft_count_words(s);
	strs = (char **)ft_calloc((word_count + 1), sizeof(char *));
	if (!strs)
		return (NULL);
	if (word_count == 0)
	{
		strs[0] = NULL;
		return (strs);
	}
	strs = ft_fill_strs(s, strs);
	return (strs);
}

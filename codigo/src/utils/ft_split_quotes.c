/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 12:07:42 by brivera@stu       #+#    #+#             */
/*   Updated: 2025/04/14 19:05:20 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	skip_word(const char *s, size_t i, bool check)
{
	bool	flag_single;
	bool	flag_double;

	flag_single = false;
	flag_double = false;
	while (s[i])
	{
		flag_single = toggle_simples(s[i], flag_single, flag_double);
		flag_double = toggle_doubles(s[i], flag_single, flag_double);
		if (check == true)
		{
			if (!flag_single && !flag_double)
			{
				if (s[i] == '"' || s[i] == '\'')
				{
					i++;
					break ;
				}
			}
		}
		else
		{
			if (!flag_single && !flag_double && ft_isspace(s[i]))
				break ;
		}
		i++;
	}
	return (i);
}

static size_t	ft_count_words(const char *s, bool check)
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
		i = skip_word(s, i, check);
	}
	return (count);
}

static char	**ft_fill_strs(char const *s, char **strs, bool check)
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
		end = skip_word(s, i, check); 
		printf("i en relleno: %zu\n", end); //borrar
		//if (check == true && s[end])
			//end++;
		strs[j] = ft_strtrim_spaces(ft_substr(s, start, end - start));
		if (!strs[j])
			return (free_array(strs));
		j++;
		i = end;
	}
	strs[j] = NULL;
	return (strs);
}

char	**ft_split_quotes(char const *s, bool check)
{
	size_t	word_count;
	char	**strs;

	if (!s)
		return (NULL);
	word_count = ft_count_words(s, check);
	strs = (char **)ft_calloc((word_count + 1), sizeof(char *));
	if (!strs)
		return (NULL);
	if (word_count == 0)
	{
		strs[0] = NULL;
		return (strs);
	}
	strs = ft_fill_strs(s, strs, check);
	return (strs);
}

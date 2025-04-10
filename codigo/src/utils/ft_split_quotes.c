/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 12:58:54 by frivas            #+#    #+#             */
/*   Updated: 2025/04/10 15:56:07 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	skip_word(const char *s, char c, size_t i)
{
	int	flagsingle;
	int	flagdouble;

	flagsingle = 0;
	flagdouble = 0;
	while (s[i])
	{
		flagsingle = toggle_simples(s[i], flagsingle, flagdouble);
		flagdouble = toggle_doubles(s[i], flagsingle, flagdouble);
		if (!flagsingle && !flagdouble && s[i] == c)
			break ;
		i++;
	}
	return (i);
}

static size_t	ft_countnewword(const char *s, char c)
{
	size_t	count;
	size_t	i;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (!s[i])
			break ;
		count++;
		i = skip_word(s, c, i);
	}
	printf("%zu\n", count);
	return (count);
}

static char	**ft_freestrs(char **strs, size_t j)
{
	while (j > 0)
	{
		free(strs[j - 1]);
		j--;
	}
	free(strs);
	return (NULL);
}

static char	**ft_fillstrs(char const *s, char c, char **strs)
{
	size_t	i;
	size_t	j;
	size_t	lenword;

	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		lenword = 0;
		if (s[i] != c)
		{
			while ((s[i + lenword] != '\0') && (s[i + lenword] != c))
				lenword++;
			strs[j] = ft_substr(s, i, lenword);
			if (strs[j] == NULL)
				return (strs = ft_freestrs(strs, j));
			j++;
			i = skip_word(s, c, i) + i;
		}
		else
			i++;
	}
	strs[j] = NULL;
	return (strs);
}

char	**ft_split_quotes(char const *s, char c)
{
	size_t	newword;
	char	**strs;

	if (!s)
		return (NULL);
	newword = ft_countnewword(s, c);
	strs = (char **)malloc((newword + 1) * sizeof(char *));
	if (strs == NULL)
		return (NULL);
	if (newword == 0)
	{
		strs[0] = NULL;
		return (strs);
	}
	strs = ft_fillstrs(s, c, strs);
	if (strs == NULL)
		return (NULL);
	return (strs);
}

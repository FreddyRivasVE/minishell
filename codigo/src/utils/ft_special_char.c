/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_special_char.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 12:01:23 by brivera@stu       #+#    #+#             */
/*   Updated: 2025/04/30 18:36:51 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	calculate_new_len(char *str, bool squote, bool dquote)
{
	size_t	len;
	size_t	i;

	len = 0;
	i = 0;
	while (str[i])
	{
		squote = toggle_simples(str[i], squote, dquote);
		dquote = toggle_doubles(str[i], squote, dquote);
		if (str[i] == '$' && !squote && !dquote
			&& (ft_special_char(str[i + 1]) || str[i + 1] == '\0'))
		{
			len += 4;
			if (!ft_isspace(str[i + 1]) && str[i + 1] != '\0')
				i += 2;
			else
				i += 1;
			continue ;
		}
		len++;
		i++;
	}
	return (len);
}

static void	escape_aux(char **output, size_t *j, char **str, size_t *i)
{
	char	next;

	next = (*str)[*i + 1];
	(*output)[(*j)++] = '\'';
	(*output)[(*j)++] = (*str)[(*i)++];
	if (next != ' ' && next != '\0')
		(*output)[(*j)++] = (*str)[(*i)++];
	(*output)[(*j)++] = '\'';
}

static char	*reserve_memory(char *str, bool squote, bool dquote)
{
	char	*output;
	size_t	len;

	len = calculate_new_len(str, squote, dquote) + 1;
	output = ft_calloc(len, sizeof(char));
	return (output);
}

char	*ms_escape_special_chars(char *str)
{
	char	*output;
	size_t	i;
	size_t	j;
	bool	squote;
	bool	dquote;

	squote = false;
	dquote = false;
	output = reserve_memory(str, squote, dquote);
	if (!output)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		squote = toggle_simples(str[i], squote, dquote);
		dquote = toggle_doubles(str[i], squote, dquote);
		if (str[i] == '$' && !squote && !dquote && ft_special_char(str[i + 1]))
		{
			escape_aux(&output, &j, &str, &i);
			continue ;
		}
		output[j++] = str[i++];
	}
	return (output);
}

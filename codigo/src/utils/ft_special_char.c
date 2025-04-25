/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_special_char.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera@student.42madrid.com <brivera>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 12:01:23 by brivera@stu       #+#    #+#             */
/*   Updated: 2025/04/25 20:22:50 by brivera@stu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	calculate_new_len(char *input, bool squote, bool dquote)
{
	size_t	len;
	size_t	i;

	len = 0;
	i = 0;
	while (input[i])
	{
		squote = toggle_simples(input[i], squote, dquote);
		dquote = toggle_doubles(input[i], squote, dquote);
		if (input[i] == '$' && !squote && !dquote
			&& ft_special_char(input[i + 1]))
		{
			len += 4;
			if (input[i + 1] != ' ' && input[i + 1] != '\0')
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

static void	escape_aux(char **output, size_t *j, char **input, size_t *i)
{
	char	next;

	next = (*input)[*i + 1];
	(*output)[(*j)++] = '\'';
	(*output)[(*j)++] = (*input)[(*i)++];
	if (next != ' ' && next != '\0')
		(*output)[(*j)++] = (*input)[(*i)++];
	(*output)[(*j)++] = '\'';
}

static char	*reserve_memory(char *input, bool squote, bool dquote)
{
	char	*output;
	size_t	len;

	len = calculate_new_len(input, squote, dquote) + 1;
	output = ft_calloc(len, sizeof(char));
	return (output);
}

char	*ms_escape_special_chars(char *input)
{
	char	*output;
	size_t	i;
	size_t	j;
	bool	squote;
	bool	dquote;

	squote = false;
	dquote = false;
	output = reserve_memory(input, squote, dquote);
	if (!output)
		return (NULL);
	i = 0;
	j = 0;
	while (input[i])
	{
		squote = toggle_simples(input[i], squote, dquote);
		dquote = toggle_doubles(input[i], squote, dquote);
		if (input[i] == '$' && !squote && !dquote && ft_special_char(input[i + 1]))
		{
			escape_aux(&output, &j, &input, &i);
			continue ;
		}
		output[j++] = input[i++];
	}
	return (output);
}

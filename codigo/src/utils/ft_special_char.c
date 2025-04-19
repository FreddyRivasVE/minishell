/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_special_char.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 12:01:23 by brivera@stu       #+#    #+#             */
/*   Updated: 2025/04/19 16:20:02 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_special_char(int c)
{
	return (c == '$' || c == '!' || c == '_'
		|| c == '#' || c == '@' || c == '*'
		|| c == '\0' || c == ' ' || ft_isdigit(c));
}

static size_t	calculate_required_length(const char *input)
{
	size_t	len;
	size_t	i;

	len = 0;
	i = 0;
	while (input[i])
	{
		if (input[i] == '$' && is_special_char(input[i + 1]))
		{
			len += 4;
			if (input[i + 1] != ' ' && input[i + 1] != '\0')
				i += 2;
			else
				i++;
			continue ;
		}
		len++;
		i++;
	}
	return (len);
}

static void	escape_aux(char **output, size_t *j, const char **input, size_t *i)
{
	char	next;

	next = (*input)[*i + 1];
	(*output)[(*j)++] = '\'';
	(*output)[(*j)++] = (*input)[(*i)++];
	if (next != ' ' && next != '\0')
	{
		(*output)[(*j)++] = (*input)[(*i)++];
	}
	(*output)[(*j)++] = '\'';
}

static char	*reserve_memory(const char *input)
{
	size_t	required_len;
	char	*output;

	required_len = calculate_required_length(input);
	output = ft_calloc(required_len + 1, sizeof(char));
	return (output);
}

char	*ft_escape_special_chars(char *input)
{
	char	*output;
	size_t	i;
	size_t	j;

	if (!input)
		return (NULL);
	output = reserve_memory(input);
	if (!output)
		return (NULL);
	i = 0;
	j = 0;
	while (input[i])
	{
		if (input[i] == '$' && is_special_char(input[i + 1]))
		{
			escape_aux(&output, &j, (const char **)&input, &i);
			continue ;
		}
		output[j++] = input[i++];
	}
	output[j] = '\0';
	return (output);
}

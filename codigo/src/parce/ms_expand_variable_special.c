/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expand_variable_special.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:19:06 by frivas            #+#    #+#             */
/*   Updated: 2025/05/20 17:12:12 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ms_new_len_mem(char *input)
{
	int		i;
	bool	squote;
	bool	dquote;
	int		rest;
	int		new_len;

	i = 0;
	squote = false;
	dquote = false;
	rest = 0;
	new_len = 0;
	while (input[i])
	{
		squote = toggle_simples(input[i], squote, dquote);
		dquote = toggle_doubles(input[i], squote, dquote);
		if (!((squote || dquote)) && input[i] == '$' && (input[i + 1] == '\''
				|| input[i + 1] == '\"'))
			rest++;
		i++;
	}
	new_len = ft_strlen(input) - rest;
	return (new_len);
}

static char	*ms_special_dollar_quote(char *input)
{
	char	*res;
	int		i;
	int		j;
	bool	squote;
	bool	dquote;

	i = 0;
	j = 0;
	squote = false;
	dquote = false;
	res = ft_calloc(ms_new_len_mem(input) + 1, sizeof(char));
	if (!res)
		return (NULL);
	while (input[i])
	{
		squote = toggle_simples(input[i], squote, dquote);
		dquote = toggle_doubles(input[i], squote, dquote);
		if (!((squote || dquote)) && input[i] == '$' && (input[i + 1] == '\''
				|| input[i + 1] == '\"'))
			i++;
		res[j] = input[i];
		j++;
		i++;
	}
	return (res);
}

bool	ms_special_expand(t_mshell *data)
{
	char	*new_input;

	new_input = ms_escape_special_chars(data->input_row);
	if (!new_input)
		return (ms_print_perror_malloc(data), false);
	free(data->input_row);
	data->input_row = new_input;
	if (ft_strnstr(data->input_row, "$'", ft_strlen(data->input_row)) != NULL
		|| ft_strnstr(data->input_row, "$\"", \
			ft_strlen(data->input_row)) != NULL)
	{
		new_input = ms_special_dollar_quote(data->input_row);
		if (!new_input)
			return (ms_print_perror_malloc(data), false);
		free(data->input_row);
		data->input_row = new_input;
	}
	if (!ms_control_expand_heredoc(data))
		return (ms_print_perror_malloc(data), false);
	new_input = ms_expand_child(data->input_row, data);
	if (!new_input)
		return (false);
	free(data->input_row);
	data->input_row = new_input;
	return (true);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_redir_together.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 10:42:24 by frivas            #+#    #+#             */
/*   Updated: 2025/05/19 12:50:23 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ms_calculate_new_length(char *str)
{
	int		i;
	int		extra_spaces;
	bool	single_quote;
	bool	double_quote;

	i = 0;
	extra_spaces = 0;
	single_quote = false;
	double_quote = false;
	while (str[i])
	{
		single_quote = toggle_simples(str[i], single_quote, double_quote);
		double_quote = toggle_doubles(str[i], single_quote, double_quote);
		if (!single_quote && !double_quote && ft_isredirection_char(str[i]))
		{
			if (i > 0 && !ft_isspace(str[i - 1]))
				extra_spaces++;
			if (ft_isredirection_char(str[i + 1]))
				i++;
			if (!ft_isspace(str[i + 1]) && str[i + 1] != '\0')
				extra_spaces++;
		}
		i++;
	}
	return (i + extra_spaces);
}

static void	handle_redirection_chars(char *str, char *new_str, int *i, int *j)
{
	if (ft_isredirection_char(str[(*i)]))
	{
		if (ft_isredirection_char(str[(*i) + 1]))
			new_str[++(*j)] = str[++(*i)];
		if (!ft_isspace(str[(*i) + 1]) && str[(*i) + 1] != '\0')
			new_str[++(*j)] = ' ';
	}
}

static void	ms_build_new_string(char *str, char *new_str)
{
	int		i;
	int		j;
	bool	sq;
	bool	dq;

	i = 0;
	j = 0;
	sq = false;
	dq = false;
	while (str[i])
	{
		sq = toggle_simples(str[i], sq, dq);
		dq = toggle_doubles(str[i], sq, dq);
		new_str[j] = str[i];
		if (str[i + 1] != '\0' && !sq && !dq
			&& ft_isredirection_char(str[i + 1])
			&& !ft_isredirection_char(str[i]) && !ft_isspace(str[i]))
			new_str[++j] = ' ';
		if (!sq && !dq && ft_isredirection_char(str[i]))
			handle_redirection_chars(str, new_str, &i, &j);
		i++;
		j++;
	}
	new_str[j] = '\0';
}

bool	ms_redir_together(t_mshell *data)
{
	char	*new_str;
	int		new_len;

	new_len = ms_calculate_new_length(data->input_row);
	new_str = (char *)ft_calloc(new_len + 1, sizeof(char));
	if (!new_str)
	{
		data->exits = ENOMEM;
		perror("malloc");
		return (false);
	}
	ms_build_new_string(data->input_row, new_str);
	free(data->input_row);
	data->input_row = new_str;
	return (true);
}

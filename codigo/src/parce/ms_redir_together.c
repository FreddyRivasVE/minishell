/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_redir_together.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera@student.42madrid.com <brivera>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 10:42:24 by frivas            #+#    #+#             */
/*   Updated: 2025/04/25 18:25:44 by brivera@stu      ###   ########.fr       */
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
			if (ft_isredirection_char(str[i + 1]))
				i++;
			if (!ft_isspace(str[i + 1]) && str[i + 1] != '\0')
				extra_spaces++;
		}
		i++;
	}
	return (i + extra_spaces);
}

static void	ms_build_new_string(char *str, char *new_str)
{
	int		i;
	int		j;
	bool	single_quote;
	bool	double_quote;

	i = 0;
	j = 0;
	single_quote = false;
	double_quote = false;
	while (str[i])
	{
		single_quote = toggle_simples(str[i], single_quote, double_quote);
		double_quote = toggle_doubles(str[i], single_quote, double_quote);
		new_str[j] = str[i];
		if (!single_quote && !double_quote && ft_isredirection_char(str[i]))
		{
			if (ft_isredirection_char(str[i + 1]))
				new_str[++j] = str[++i];
			if (!ft_isspace(str[i + 1]) && str[i + 1] != '\0')
				new_str[++j] = ' ';
		}
		i++;
		j++;
	}
	new_str[j] = '\0';
}

char	*ms_redir_together(char *str)
{
	char	*new_str;
	int		new_len;

	new_len = ms_calculate_new_length(str);
	new_str = (char *)ft_calloc(new_len + 1, sizeof(char));
	if (!new_str)
		return (NULL);
	ms_build_new_string(str, new_str);
	return (new_str);
}

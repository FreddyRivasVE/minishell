/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_quotes_killer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 18:08:26 by frivas            #+#    #+#             */
/*   Updated: 2025/05/20 16:51:40 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ms_quotes_killer_aux(char **split, bool flag)
{
	int		i;
	char	*result;
	char	*temp;

	i = 0;
	result = ft_calloc(1, sizeof(char));
	if (!result)
		return (free_array(split), NULL);
	while (split[i])
	{
		if (!flag && (split[i][0] == '\'' || split[i][0] == '\"'))
		{
			temp = ft_substr(split[i], 1, ft_strlen(split[i]) - 2);
			result = ft_strjoin_free(result, temp);
		}
		else
			result = ft_strjoin_free(result, ft_strdup(split[i]));
		i++;
	}
	return (free_array(split), result);
}

bool	ms_is_quoted_redirection(char *s)
{
	return (!ft_strcmp(s, "\"<<\"") || !ft_strcmp(s, "\"<\"")
		|| !ft_strcmp(s, "\">\"") || !ft_strcmp(s, "\">>\"")
		|| !ft_strcmp(s, "\'<<\'") || !ft_strcmp(s, "\'<\'")
		|| !ft_strcmp(s, "\'>\'") || !ft_strcmp(s, "\'>>\'"));
}

bool	ms_process_input_row(char **row, t_mshell *data)
{
	int		j;
	char	**temp;
	bool	flag;

	j = 0;
	flag = false;
	while (row[j])
	{
		temp = ft_split_quotes(row[j], true);
		if (!temp)
			return (ms_print_perror_malloc(data), false);
		if (j > 0 && (!ft_strcmp(row[j - 1], "<<")))
			flag = true;
		if (row[j] != NULL && ms_is_quoted_redirection(row[j]))
			flag = true;
		free(row[j]);
		row[j] = ms_quotes_killer_aux(temp, flag);
		if (!row[j])
			return (ms_print_perror_malloc(data), false);
		j++;
		flag = false;
	}
	return (true);
}

bool	ms_quotes_killer(char ***inputs, t_mshell *data)
{
	int	i;

	i = 0;
	while (inputs[i])
	{
		if (!ms_process_input_row(inputs[i], data))
			return (false);
		i++;
	}
	return (true);
}

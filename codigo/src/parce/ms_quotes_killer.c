/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_quotes_killer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 18:08:26 by frivas            #+#    #+#             */
/*   Updated: 2025/05/16 15:23:15 by frivas           ###   ########.fr       */
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

bool	ms_quotes_killer(char ***inputs, t_mshell *data)
{
	int		i;
	int		j;
	char	**temp;
	bool	flag;

	i = 0;
	flag = false;
	while (inputs[i])
	{
		j = 0;
		while (inputs[i][j])
		{
			temp = ft_split_quotes(inputs[i][j], true);
			if (!temp)
				return (ms_print_perror_malloc(data), false);
			if (j > 0 && (!ft_strcmp(inputs[i][j - 1], "<<")))
				flag = true;
			if (inputs[i][j] != NULL && ms_is_quoted_redirection(inputs[i][j]))
				flag = true;
			free(inputs[i][j]);
			inputs[i][j] = ms_quotes_killer_aux(temp, flag);
			if (!inputs[i][j])
				return (ms_print_perror_malloc(data), false);
			j++;
			flag = false;
		}
		i++;
	}
	return (true);
}

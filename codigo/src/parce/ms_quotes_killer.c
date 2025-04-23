/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_quotes_killer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 18:08:26 by frivas            #+#    #+#             */
/*   Updated: 2025/04/23 20:18:10 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ms_quotes_killer_aux(char **split)
{
	int		i;
	char	*result;
	char	*temp;

	i = 0;
	result = ft_calloc(1, sizeof(char));
	if (!result)
		return (NULL);
	while (split[i])
	{
		if (split[i][0] == '\'' || split[i][0] == '\"')
		{
			temp = ft_substr(split[i], 1, ft_strlen(split[i]) - 2);
			result = ft_strjoin_free(result, temp);
		}
		else
		{
			temp = ft_strdup(split[i]);
			result = ft_strjoin_free(result, temp);
		}
		i++;
	}
	free_array(split);
	return (result);
}

void	ms_quotes_killer(char ***inputs)
{
	int		i;
	int		j;
	char	**temp;

	i = 0;
	while (inputs[i])
	{
		j = 0;
		while (inputs[i][j])
		{
			temp = ft_split_quotes(inputs[i][j], true);
			free(inputs[i][j]);
			inputs[i][j] = ms_quotes_killer_aux(temp);
			j++;
		}
		i++;
	}
}

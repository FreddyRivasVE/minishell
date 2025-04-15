/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expand_variable.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 15:41:56 by frivas            #+#    #+#             */
/*   Updated: 2025/04/15 20:19:46 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ms_found_word_aux(char *toexpand, int i, char *result, char *expand)
{
	char	*strtemp;
	char	*word;
	int		start;
	int		end;

	strtemp = NULL;
	if (expand)
	{
		strtemp = ft_strjoin(result, expand);
		free(result);
		result = ft_strdup(strtemp);
		free(strtemp);
	}
	if (toexpand[i] && toexpand[i] != '\"' && toexpand[i] != '$')
	{
		start = i;
		while (toexpand[i] != '\"' && toexpand[i] != '$' && toexpand[i])
			i++;
		end = i;
		word = ft_substr(toexpand, start, end - start);
		strtemp = ft_strjoin(result, word);
		free(result);
		return (free(word), strtemp);
	}
	return (result);
}

char	*ms_found_word(char *toexpand, t_list **env, int i, char *result)
{
	int		start;
	int		end;
	char	*word;
	char	*expand;

	i++;
	start = i;
	while (toexpand[i] != '$' && toexpand [i] != '\"'
		&& !(ft_isspace(toexpand[i])) && toexpand[i] && toexpand[i] != '\'')
		i++;
	end = i;
	word = ft_substr(toexpand, start, end - start);
	expand = ft_list_extract_if(env, word, var_cmp);
	result = ms_found_word_aux(toexpand, i, result, expand);
	return (free(word), ms_free_ptr(expand), result);
}


char	*ms_expand_str(char *toexpand, t_list **env)
{
	int		start;
	int		end;
	char	*result;
	int		i;

	i = 0;
	if (toexpand[i] == '\'')
		return (toexpand);
	if (toexpand[i] == '\"')
		i++;
	start = i;
	while (toexpand[i] != '$')
		i++;
	end = i;
	result = ft_substr(toexpand, start, end - start);
	while (toexpand[i])
	{
		if (toexpand[i] == '$')
			result = ms_found_word(toexpand, env, i, result);
		i++;
	}
	return (result);
}

char	*ms_expand_child(char *str, t_list **env)
{
	char	**expandsplit;
	int		i;
	char	*found_word;
	char	*temp;
	char	*result;

	expandsplit = ft_split_quotes(str, true);
	result = ft_calloc(1, sizeof(char));
	i = 0;
	while (expandsplit[i])
	{
		if (ft_strchr(expandsplit[i], '$'))
		{
			found_word = ms_expand_str(expandsplit[i], env);
			ms_free_ptr(expandsplit[i]);
			expandsplit[i] = found_word;
		}
		temp = result;
		result = ft_strjoin(temp, expandsplit[i]);
		ms_free_ptr(temp);
		i++;
	}
	free_array(expandsplit);
	return (result);
}

int	ms_expand_variable(t_mshell *data)
{
	int		i;
	int		j;
	char	***toexpand;
	char	*temp;

	i = 0;
	toexpand = data->inputs->splitaftpipes;
	while (toexpand[i])
	{
		j = 0;
		while (toexpand[i][j])
		{
			if (ft_strchr(toexpand[i][j], '$'))
			{
				temp = ms_expand_child(toexpand[i][j], &data->env);
				ms_free_ptr(toexpand[i][j]);
				toexpand[i][j] = temp;
			}
			j++;
		}
		i++;
	}
	return (0);
}

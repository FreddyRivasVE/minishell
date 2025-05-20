/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_control_expand_heredoc.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 15:29:32 by frivas            #+#    #+#             */
/*   Updated: 2025/05/20 21:18:14 by brivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool ms_control_expand_heredoc(char *str, int pos, t_mshell *data)
{
	int		i;
	bool	dobleq;

	dobleq = data->flag;
	i = pos - 1;
	while (i >= 0 && (ft_isspace(str[i]) || str[i] == '\"'))
	{
		if (str[i] == '\"' && dobleq)
			dobleq = false;
		else if (str[i] == '\"' && !dobleq)
			dobleq = true;
		i--;
	}
	if (i > 0 && str[i] == '<' && str[i-1] == '<' && dobleq == 0) 
		return (true);
	return (false);
}

/*
char	*ms_heredoc_case(int *i, char *str, char *result)
{
	int		start;
	int		end;

	start = *i;
	(*i) = (*i) + 2;
	end = (*i);
	result = ft_strjoin_free(result, ft_substr(str, start, end - start));
	start = (*i);
	while (str[(*i)] && str[(*i)] != '\'' && str[(*i)] != '\"'
		&& str[(*i)] != '$')
		(*i)++;
	end = (*i);
	result = ft_strjoin_free(result, ft_substr(str, start, end - start));
	if (str[(*i)] == '$')
	{
		result = ft_strjoin_free(result, ft_strdup("\'"));
		start = (*i);
		while (str[(*i)] && !ft_isspace(str[(*i)]))
			(*i)++;
		end = (*i);
		result = ft_strjoin_free(result, ft_substr(str, start, end - start));
		result = ft_strjoin_free(result, ft_strdup("'"));
	}
	else if (str[(*i)] == '\"')
	{
		result = ft_strjoin_free(result, ft_strdup("'"));
		(*i)++;
		start = (*i);
		while (str[(*i)] && str[(*i)] != '\"')
			(*i)++;
		end = (*i);
		result = ft_strjoin_free(result, ft_substr(str, start, end - start));
		result = ft_strjoin_free(result, ft_strdup("'"));
		(*i)++;
	}
	else
	{
		start = (*i);
		while (str[(*i)] && str[(*i)] != '\'')
			(*i)++;
		end = (*i);
		result = ft_strjoin_free(result, ft_substr(str, start, end - start));
	}
	return (result);
}

static char	*ms_read_str(char *temp, char *str)
{
	int		i;
	bool	sq;
	bool	dq;
	int		start;
	int		end;

	i = 0;
	sq = false;
	dq = false;
	while (str[i])
	{
		start = i;
		while (str[i] && str[i] != '<')
		{
			sq = toggle_simples(str[i], sq, dq);
			dq = toggle_doubles(str[i], sq, dq);
			i++;
		}
		end = i;
		temp = ft_strjoin_free(temp, ft_substr(str, start, end - start));
		start = i;
		if (str[i] != '\0' && str[i + 1] && str[i + 1] == '<' && !(sq || dq))
			temp = ms_heredoc_case(&i, str, temp);
		else if (str[i])
		{
			end = i + 1;
			temp = ft_strjoin_free(temp, ft_substr(str, start, end - start));
			i++;
		}
	}
	return (temp);
}

bool	ms_control_expand_heredoc(t_mshell *data)
{
	char	*temp;

	temp = ft_calloc(1, sizeof(char));
	if (!temp)
		return (false);
	temp = ms_read_str(temp, data->input_row);
	if (!temp)
		return (false);
	free(data->input_row);
	data->input_row = temp;
	return (true);
}
*/

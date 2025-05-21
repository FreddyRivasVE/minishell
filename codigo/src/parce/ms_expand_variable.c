/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expand_variable.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 15:41:56 by frivas            #+#    #+#             */
/*   Updated: 2025/05/20 23:19:03 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ms_found_word(char *toexp, t_mshell *data, int *i, char *result)
{
	int		start;
	int		end;
	char	*word;
	char	*expand;

	(*i)++;
	start = *i;
	while (toexp[*i] != '$' && toexp [*i] != '\"' && !(ft_isspace(toexp[*i]))
		&& toexp[*i] && toexp[*i] != '\'' && toexp[*i] != '=')
		(*i)++;
	end = *i;
	word = ft_substr(toexp, start, end - start);
	if (!word)
		return (ms_print_perror_malloc(data), NULL);
	expand = ft_list_extract_if(&data->env, word, var_cmp);
	if (expand && data->flag == 0 && data->hdflag != MODE_HEREDOC)
		expand = ms_block_expand_var(expand, data);
	else
		expand = ms_qd_kill(expand);
	if (expand)
		result = ft_strjoin_free(result, expand);
	return (ft_free_ptr((void **)&word), result);
}

static char	*ms_router_expand(char *str, int *i, char *res, t_mshell *data)
{
	int		start;
	int		end;

	end = *i;
	start = *i;
	if (str[*i + 1] == '\0')
		return (ft_strjoin_free(res, ft_substr(str, start, ++end - start)));
	if (ms_control_expand_heredoc(str, *i, data))
		return ((*i)++, ft_strjoin_free(res, ft_substr(str, start, 1)));
	if (str[*i] == '$')
	{
		if (str[*i + 1] == '?')
			return ((*i)++, (*i)++, ft_strjoin_free(res, ft_itoa(data->exits)));
		if (ft_special_char(str[*i + 1]))
		{
			(*i) = (*i) + 2;
			end = *i;
			return (ft_strjoin_free(res, ft_substr(str, start, end - start)));
		}
		if (ft_isspace(str[*i + 1]) || str[*i + 1] == '\"'
			|| (str[*i + 1] == '\'' && str[0] == '\"'))
			return ((*i)++, ft_strjoin_free(res, ft_substr(str, start, 1)));
		return (ms_found_word(str, data, i, res));
	}
	return (ft_strjoin_free(res, ft_substr(str, *i, 1)));
}

static char	*ms_expand_part(char *str, int *i, bool *sq, bool *dq)
{
	int		start;
	int		end;

	start = *i;
	*sq = toggle_simples(str[*i], *sq, *dq);
	*dq = toggle_doubles(str[*i], *sq, *dq);
	while (str[*i] && str[*i] != '$' && !(*sq))
	{
		(*i)++;
		*sq = toggle_simples(str[*i], *sq, *dq);
		*dq = toggle_doubles(str[*i], *sq, *dq);
	}
	if (*sq)
	{
		while (str[*i] && *sq)
		{
			(*i)++;
			*sq = toggle_simples(str[*i], *sq, *dq);
			*dq = toggle_doubles(str[*i], *sq, *dq);
		}
		(*i)++;
	}
	end = *i;
	return (ft_substr(str, start, end - start));
}

static char	*ms_expand_loop(char *str, char *res, t_mshell *data)
{
	int		i;
	bool	sq;
	bool	dq;
	char	*tmp;

	i = 0;
	sq = false;
	dq = false;
	while (str[i])
	{
		tmp = ms_expand_part(str, &i, &sq, &dq);
		if (!tmp)
			return (free(res), ms_print_perror_malloc(data), NULL);
		res = ft_strjoin_free(res, tmp);
		if (!res)
			return (ms_print_perror_malloc(data), NULL);
		if (str[i] == '$')
		{
			data->flag = dq;
			res = ms_router_expand(str, &i, res, data);
		}
		if (!res && data->exits == ENOMEM)
			return (NULL);
	}
	return (res);
}

char	*ms_expand_child(char *str, t_mshell *data)
{
	char	*result;

	result = ft_calloc(1, sizeof(char));
	if (!result)
	{
		ms_print_perror_malloc(data);
		return (NULL);
	}
	return (ms_expand_loop(str, result, data));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expand_variable.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 15:41:56 by frivas            #+#    #+#             */
/*   Updated: 2025/05/16 12:52:35 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ms_found_word(char *toexpand, t_mshell *data, int *i, char *result)
{
	int		start;
	int		end;
	char	*word;
	char	*expand;

	(*i)++;
	start = *i;
	while (toexpand[*i] != '$' && toexpand [*i] != '\"'
		&& !(ft_isspace(toexpand[*i])) && toexpand[*i] && toexpand[*i] != '\'')
		(*i)++;
	end = *i;
	word = ft_substr(toexpand, start, end - start);
	if (!word)
	{
		ms_print_perror_malloc(data);
		return (NULL);
	}
	expand = ft_list_extract_if(&data->env, word, var_cmp);
	if (expand)
		result = ft_strjoin_free(result, expand);
	return (free(word), result);
}

char	*ms_router_expand(char *toexpand, int *i, char *result, t_mshell *data)
{
	int		start;
	int		end;

	end = *i;
	start = *i;
	if (toexpand[*i + 1] == '\0')
		return (ft_strjoin_free(result, \
		ft_substr(toexpand, start, ++end - start)));
	if (toexpand[*i] == '$')
	{
		if (toexpand[*i + 1] == '?')
			return ((*i)++, (*i)++, ft_strjoin_free(result, ft_itoa(data->exits)));
		if (ft_special_char(toexpand[*i + 1]))
		{
			(*i)++;
			end = *i + 1;
			return (ft_strjoin_free(result, \
			ft_substr(toexpand, start, end - start)));
		}
		if (ft_isspace(toexpand[*i + 1]) || toexpand[*i + 1] == '\"'
			|| (toexpand[*i + 1] == '\'' && toexpand[0] == '\"'))
			return ((*i)++, ft_strjoin_free(result, ft_substr(toexpand, start, 1)));
		return (ms_found_word(toexpand, data, i, result));
	}
	return (ft_strjoin_free(result, ft_substr(toexpand, *i, 1)));
}

char	*ms_expand_child(char *str, t_mshell *data)
{
	int		i;
	bool	simpleq;
	bool	doubleq;
	int		start;
	int		end;
	char	*temp;
	char	*result;

	i = 0;
	simpleq = false;
	doubleq = false;
	result = ft_calloc(1, sizeof(char));
	while (str[i])
	{
		start = i;
		simpleq = toggle_simples(str[i], simpleq, doubleq);
		doubleq = toggle_doubles(str[i], simpleq, doubleq);
		while (str[i] && str[i] != '$' && !simpleq)
		{
			i++;
			simpleq = toggle_simples(str[i], simpleq, doubleq);
			doubleq = toggle_doubles(str[i], simpleq, doubleq);
		}
		if (simpleq)
		{
			while (str[i] && simpleq)
			{
				i++;
				simpleq = toggle_simples(str[i], simpleq, doubleq);
				doubleq = toggle_doubles(str[i], simpleq, doubleq);
			}
			i++;
		}
		printf("valor de ix: %d\n", i); //borrar
		end = i;
		temp = ft_substr(str, start, end - start);
		result = ft_strjoin_free(result, temp);
		if (str[i] == '$')
			result = ms_router_expand(str, &i, result, data);
		if (!result && data->exits == ENOMEM)
			return (NULL);
	}
	return (result);
}

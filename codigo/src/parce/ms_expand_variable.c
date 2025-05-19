/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expand_variable.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 15:41:56 by frivas            #+#    #+#             */
/*   Updated: 2025/05/19 20:42:47 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ms_found_word(char *toexpand, t_mshell *data, int *i, char *result, int flag)
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
	if (expand && flag == 0)
		expand = ms_block_expand_var(expand, data);
	else
	{
		ft_free_ptr((void **)&word);
		word = ft_substr(expand, 1, ft_strlen(expand) - 2);
		ft_free_ptr((void **)&expand);
		expand = ft_strdup(word);
		
	}
	if (expand)
		result = ft_strjoin_free(result, expand);
	printf("resul expand: %s\n", result); //borrar
	return (ft_free_ptr((void **)&word), result);
}

static char	*ms_router_expand(char *str, int *i, char *res, t_mshell *data, int flag)
{
	int		start;
	int		end;

	end = *i;
	start = *i;
	if (str[*i + 1] == '\0')
		return (ft_strjoin_free(res, ft_substr(str, start, ++end - start)));
	if (str[*i] == '$')
	{
		if (str[*i + 1] == '?')
			return ((*i)++, (*i)++, ft_strjoin_free(res, ft_itoa(data->exits)));
		if (ft_special_char(str[*i + 1]))
		{
			(*i) = (*i) + 2;
			end = *i;
			printf("i: %d start: %d end: %d res: %s\n", *i, start, end, res); //borrar
			return (ft_strjoin_free(res, ft_substr(str, start, end - start)));
		}
		if (ft_isspace(str[*i + 1]) || str[*i + 1] == '\"'
			|| (str[*i + 1] == '\'' && str[0] == '\"'))
			return ((*i)++, ft_strjoin_free(res, ft_substr(str, start, 1)));
		return (ms_found_word(str, data, i, res, flag));
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
	int		flag;

	i = 0;
	flag = 0;
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
			if (dq)
				flag = 1;
			res = ms_router_expand(str, &i, res, data, flag);
			flag = 0;
			printf("regresa: %s\n", res); //borrar
		}
		if (!res && data->exits == ENOMEM)
			return (NULL);
	}
	printf("expand final: %s\n", res); //borrar
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

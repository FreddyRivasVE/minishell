/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expand_variable.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 15:41:56 by frivas            #+#    #+#             */
/*   Updated: 2025/05/15 18:23:49 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ms_found_word(char *toexpand, t_list **env, int *i, char *result)
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
	expand = ft_list_extract_if(env, word, var_cmp);
	if (expand)
		result = ft_strjoin_free(result, expand);
	//(*i)--;
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
			return ((*i)++, ft_strjoin_free(result, ft_itoa(data->exits)));
		if (ft_special_char(toexpand[*i + 1]))
		{
			(*i)++;
			end = *i + 1;
			return (ft_strjoin_free(result, \
			ft_substr(toexpand, start, end - start)));
		}
		if (ft_isspace(toexpand[*i + 1]) || toexpand[*i + 1] == '\"'
			|| (toexpand[*i + 1] == '\'' && toexpand[0] == '\"'))
			return (ft_strjoin_free(result, ft_substr(toexpand, *i, 1)));
		return (ms_found_word(toexpand, &data->env, i, result));
	}
	return (ft_strjoin_free(result, ft_substr(toexpand, *i, 1)));
}

/* char	*ms_expand_str(char *toexpand, t_mshell *data)
{
	char	*result;
	int		i;

	i = 0;
	if (toexpand[i] == '\'')
	{
		result = ft_strdup(toexpand);
		return (result);
	}
	result = ft_calloc(1, sizeof(char));
	if (!result)
		return (NULL);
	while (toexpand[i])
	{
		result = ms_router_expand(toexpand, &i, result, data);
		i++;
	}
	return (result);
} */

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
//	temp = ft_calloc(1, sizeof(char));
	printf("entra: %s\n", str); //borrar
	result = ft_calloc(1, sizeof(char));
	while (str[i])
	{
		printf("i: [%d] entro\n", i); //borrar
		simpleq = toggle_simples(str[i], simpleq, doubleq);
		doubleq = toggle_doubles(str[i], simpleq, doubleq);
		if (simpleq)
		{
			start = i;
			while (str[i] && simpleq)
			{
				i++;
				simpleq = toggle_simples(str[i], simpleq, doubleq);
				doubleq = toggle_doubles(str[i], simpleq, doubleq);
			}
			end = i;
			temp = ft_substr(str, start, end - start);
			result = ft_strjoin_free(result, temp);
			i++;
		}
		else
		{
			start = i;
			while (str[i] && str[i] != '$')
			{
				i++;
			}
			printf("valor de i: %d\n", i); //borrar
			if (i > 0 && str[i] && str[i] == '$' && str[i - 1] == '\'' && str[i + 1] == '\'')
				i = i + 2;
			end = i;
			temp = ft_substr(str, start, end - start);
			printf("temp [%d]: %s\n", i, temp);// borrar
			result = ft_strjoin_free(result, temp);
			if (str[i] == '$')
			{
				printf("res: %s\n", result); //borrar
				printf("str: %s\n", str); //borrar
				result = ms_router_expand(str, &i, result, data);
				printf("regresa: %s\n", result); //borrar
			}
		}
		printf("valor de i letra: %c: %d\n", str[i - 1], i); //borrar
		
		//i++;
	}
	return (result);
}

/* 	expandsplit = ft_split_quotes(str, true);
	result = ft_calloc(1, sizeof(char));
	if (!result || !expandsplit)
		return (free_array(expandsplit), ft_free_ptr((void **)&result), NULL);
	i = 0;
	while (expandsplit[i])
	{
		if (ft_strchr(expandsplit[i], '$'))
		{
			found_word = ms_expand_str(expandsplit[i], data);
			ft_free_ptr((void **)&expandsplit[i]);
			expandsplit[i] = found_word;
		}
		temp = result;
		result = ft_strjoin(temp, expandsplit[i]);
		ft_free_ptr((void **)&temp);
		i++;
	}
	return (free_array(expandsplit), result);
} */

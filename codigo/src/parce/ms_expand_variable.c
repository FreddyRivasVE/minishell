/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expand_variable.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 15:41:56 by frivas            #+#    #+#             */
/*   Updated: 2025/04/23 00:09:53 by frivas           ###   ########.fr       */
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
	printf("%d\n", *i); // borrar
	if (expand)
		result = ft_strjoin_free(result, expand);
	(*i)--;
	return (free(word), result);
}

char	*ms_router_expand(char *toexpand, int *i, char *result, t_list **env)
{
	int		start;
	int		end;
	char	*temp;

	end = *i;
	printf("quien es toexpand [i]: %c\n", toexpand [*i]); //borrar
	start = *i;
	if (toexpand[*i + 1] == '\0')
	{
		(*i)++;
		end = (*i);
		temp = ft_substr(toexpand, start, end - start);
		result = ft_strjoin_free(result, temp);
		return (result);
	}
	else if (toexpand[*i] == '$')
	{
		if (special_char(toexpand[*i + 1]))
		{
			(*i)++;
			end = (*i + 1);
			temp = ft_substr(toexpand, start, end - start);
			result = ft_strjoin_free(result, temp);
			printf("agregados a result: %s\n", result); //borrar
			*i = end - 1;
			printf("devuelve %d\n", *i); //borrar
			return (result);
		}
		else if (ft_isspace(toexpand[*i + 1]))
			result = ft_strjoin_free(result, ft_substr(toexpand, *i, 1));
		else
			result = ms_found_word(toexpand, env, i, result);
	}
	else if (toexpand[*i] != '\0')
		result = ft_strjoin_free(result, ft_substr(toexpand, *i, 1));
	return (result);
}

char	*ms_expand_str(char *toexpand, t_list **env)
{
	char	*result;
	int		i;

	i = 0;
	if (toexpand[i] == '\'')
	{
		result = ft_strdup(toexpand);
		printf("test brenda: %s\n", result);
		return (result);
		//return (ft_substr(toexpand, 1, (ft_strlen(toexpand) - 2)));
	}
	//if (toexpand[i] == '\"')
	//	i++;
	result = ft_calloc(1, sizeof(char));
	while (toexpand[i])
	{
		if (ft_isspace(toexpand[i]))
		{
			//result = ft_strjoin_free(result, ft_substr(toexpand, i, 1)); se debe eliminar el if ft_isspace?
			printf("result espacio: %sR\n", result); //borrar
		}
		printf("%d\n", i); //borrar
		result = ms_router_expand(toexpand, &i, result, env);
		i++;
		printf("ronda completa\n");
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
	ft_print_array(expandsplit); //borrar
	result = ft_calloc(1, sizeof(char));
	i = 0;
	while (expandsplit[i])
	{
		if (ft_strchr(expandsplit[i], '$'))
		{
			found_word = ms_expand_str(expandsplit[i], env);
			ft_free_ptr(expandsplit[i]);
			expandsplit[i] = found_word;
		}
		temp = result;
		result = ft_strjoin(temp, expandsplit[i]);
		ft_free_ptr(temp);
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
	ft_print_array_triple(toexpand); // BORRAR
	while (toexpand[i])
	{
		j = 0;
		while (toexpand[i][j])
		{
			if (ft_strchr(toexpand[i][j], '$'))
			{
				temp = ms_expand_child(toexpand[i][j], &data->env);
				ft_free_ptr(toexpand[i][j]);
				toexpand[i][j] = temp;
			}
			j++;
		}
		i++;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expand_variable.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 15:41:56 by frivas            #+#    #+#             */
/*   Updated: 2025/04/14 20:18:08 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ms_found_word(char *toexpand)
{
	int		start;
	int		end;
	char	*result;
	int		i;

	start = ft_strcspn(toexpand, "$") + 1;
	i = start;
	while (toexpand[i] && toexpand[i] != '\"')
		i++;
	if (toexpand[i] == '"')
		end = i - 2;
	else
		end = i - 1;
	result = ft_substr(toexpand, start, end);
	return (result);
}


char	*ft_list_extract_if(t_list **begin_list, void *data_ref, int (*cmp)())
{
	t_list	*cur;
	size_t	start;
	size_t	end;
	char	*res;

	if (!begin_list || !*begin_list)
		return (NULL);
	cur = *begin_list;
	if (cmp(cur->content, data_ref) == 0)
	{
		end = ft_strlen((char *)cur->content);
		start = ft_strcspn((char *)cur->content, "=") + 1;
		res = ft_substr((char *)cur->content, start, end);
		return (res);
	}
	if (cur->next)
		return (ft_list_extract_if(&(cur->next), data_ref, cmp));
	return (NULL);
}

char	*ms_expand_child(char *str, t_list **env)
{
	char	**expandsplit;
	int		i;
	char	*found_word;
	char	*temp;
	char	*result;

	
	expandsplit = ft_split_quotes(str, true);
	printf("----->split por comillas argumento\n"); //borrar
	ft_print_array(expandsplit); //borrar 
	result = ft_calloc(1, sizeof(char));
	i = 0;
	while (expandsplit[i])
	{
		if (ft_strchr(expandsplit[i], '$'))
		{
			found_word = ms_found_word(expandsplit[i]);
			temp = ft_list_extract_if(env, found_word, var_cmp);
			ms_free_ptr(found_word);
			ms_free_ptr(expandsplit[i]);
			expandsplit[i] = temp;
		}
		temp = result;
		result = ft_strjoin(temp, expandsplit[i]);
		ms_free_ptr(temp);
		printf("RESULT %s\n", result); //Borrar
		i++;
	}
	ft_print_array(expandsplit);
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

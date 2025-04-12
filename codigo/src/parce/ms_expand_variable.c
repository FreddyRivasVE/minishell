/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expand_variable.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 15:41:56 by frivas            #+#    #+#             */
/*   Updated: 2025/04/12 18:37:25 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


char	*ft_list_extract_if(t_list **begin_list, void *data_ref, int (*cmp)())
{
	t_list	*cur;
	char	*temp;
	size_t	start;
	size_t	end;
	char	*res;

	if (!begin_list || !*begin_list)
		return (NULL);
	temp = ft_substr(data_ref, 1, ft_strlen(data_ref));
	cur = *begin_list;
	if (cmp(cur->content, temp) == 0)
	{
		printf("%s\n", (char *)cur->content);
		end = ft_strlen((char *)cur->content);
		start = ft_strcspn((char *)cur->content, "=") + 1;
		free(temp);
		res = ft_substr((char *)cur->content, start, end);
		return (res);
	}
	if (cur->next)
	{
		free(temp);
		return (ft_list_extract_if(&(cur->next), data_ref, cmp));
	}
	free(temp);
	return (NULL);
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
				temp = ft_list_extract_if(&data->env, toexpand[i][j], var_cmp);
				printf("%s\n", temp);
				ms_free_ptr(toexpand[i][j]);
				toexpand[i][j] = temp;
				printf("ENTRO [%d][%d]\n", i, j); //Borrar
			}
			j++;
		}
		i++;
	}
	return (0);
}

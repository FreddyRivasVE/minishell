/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_move_env_to_pointer.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-24 11:52:11 by brivera           #+#    #+#             */
/*   Updated: 2025-05-24 11:52:11 by brivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ms_kill_dquotes_v2(char *str)
{
	char	*result;
	int		i;
	int		j;
	int		flag;

	flag = 0;
	result = ft_calloc(ft_strlen(str), sizeof(char));
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i] != 0)
	{
		if (str[i] == '\"' && str[i + 1] == '\0')
			break ;
		result[j] = str[i];
		if (str[i] == '=' && flag == 0)
		{
			i++;
			flag = 1;
		}
		i++;
		j++;
	}
	return (result);
}

void	ms_move_env_to_pointer(t_mshell *data)
{
	int		count;
	t_list	*lst;
	int		i;

	i = 0;
	count = ft_lstsize(data->env);
	data->envp = ft_calloc(count + 1, sizeof(char *));
	if (!data->envp)
	{
		ms_print_perror_malloc(data);
		return ;
	}
	lst = data->env;
	while (lst != NULL)
	{
		data->envp[i] = ms_kill_dquotes_v2(lst->content);
		if (!data->envp[i])
		{
			ms_print_perror_malloc(data);
			free_array(data->envp);
			return ;
		}
		i++;
		lst = lst->next;
	}
}

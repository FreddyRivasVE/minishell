/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_01.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 19:36:51 by brivera@stu       #+#    #+#             */
/*   Updated: 2025/09/04 12:11:28 by brivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*ms_copy_export_env(t_list **env)
{
	char	*envread;
	t_list	*new_node;
	t_list	*env_list;
	t_list	*current;

	env_list = NULL;
	current = *env;
	while (current != NULL)
	{
		envread = ft_strdup(current->content);
		if (!envread)
			return (perror("minishell: malloc"), ft_lstclear(&env_list, free),
				env_list);
		new_node = ft_lstnew(envread);
		if (!new_node)
			return (perror("minishell: molloc"), ft_free_ptr((void *)envread),
				ft_lstclear(&env_list, free), env_list);
		ft_lstadd_back(&env_list, new_node);
		current = current->next;
	}
	return (env_list);
}

int	ft_list_replace_cont(t_list **begin_list, void *ref, int (*cmp)())
{
	t_list	*cur;
	int		end;
	char	*cutref;

	if (!begin_list || !*begin_list)
		return (0);
	end = ft_strcspn(ref, "=");
	cutref = ft_substr(ref, 0, end);
	cur = *begin_list;
	if (cmp(cur->content, cutref) == 0)
	{
		ft_free_ptr((void **)&cur->content);
		cur->content = ref;
		free(cutref);
		return (1);
	}
	else
		return (free(cutref), ft_list_replace_cont(&cur->next, ref, cmp));
	return (0);
}

char	*ms_add_dquotes(char *str)
{
	char	*result;
	int		i;
	int		j;
	int		flag;

	flag = 0;
	result = ft_calloc(ft_strlen(str) + 3, sizeof(char));
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i] != 0)
	{
		result[j] = str[i];
		if (str[i] == '=' && flag == 0)
		{
			result[++j] = '\"';
			flag = 1;
		}
		i++;
		j++;
	}
	if (flag == 1)
		result[j] = '\"';
	return (result);
}

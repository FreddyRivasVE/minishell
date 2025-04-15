/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_extract_if.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 19:21:42 by frivas            #+#    #+#             */
/*   Updated: 2025/04/15 19:22:34 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

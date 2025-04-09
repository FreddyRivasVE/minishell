/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_remove_if.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 14:35:54 by frivas            #+#    #+#             */
/*   Updated: 2025/04/09 15:15:24 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)())
{
	t_list	*cur;

	if (!begin_list || !*begin_list)
		return ;
	cur = *begin_list;
	if (cmp(cur->content, data_ref) == 0)
	{
		*begin_list = cur->next;
		ft_lstdelone(cur, free);
		ft_list_remove_if(begin_list, data_ref, cmp);
	}
	else
		ft_list_remove_if(&cur->next, data_ref, cmp);
}

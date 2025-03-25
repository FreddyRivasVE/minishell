/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera@student.42madrid.com <brivera>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 15:26:45 by brivera           #+#    #+#             */
/*   Updated: 2025/02/27 19:23:02 by brivera@stu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *news)
{
	t_list	*aux;

	if (!lst || !news)
		return ;
	if (!*lst)
	{
		*lst = news;
		return ;
	}
	aux = ft_lstlast(*lst);
	aux->next = news;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 12:33:49 by frivas            #+#    #+#             */
/*   Updated: 2025/03/25 12:34:21 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_list_content_char(t_list **lst)
{
	t_list *current = *lst;
	
	while (current != NULL)
	{
		if (current->content != NULL)
		{
			printf("%s\n", (char *)current->content);
			current = current->next;
		}
	}
}
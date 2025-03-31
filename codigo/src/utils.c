/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 12:33:49 by frivas            #+#    #+#             */
/*   Updated: 2025/03/31 12:16:27 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_list_content_char(t_list **lst)
{
	t_list	*current;

	current = *lst;
	while (current != NULL)
	{
		if (current->content != NULL)
		{
			printf("%s\n", (char *)current->content);
			current = current->next;
		}
	}
}

size_t	ft_strspn(const char *s, const char *accept)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (ft_strchr(accept, s[i]) == 0)
			break ;
		++i;
	}
	return (i);
}

size_t	ft_strcspn(const char *s, const char *reject)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (s[i] != '\0')
	{
		while (reject[k] != '\0')
		{
			if (s[i] == reject[k])
				return (i);
			k++;
		}
		k = 0;
		i++;
	}
	return (i);
}

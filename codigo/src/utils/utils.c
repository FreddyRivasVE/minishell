/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 12:33:49 by frivas            #+#    #+#             */
/*   Updated: 2025/04/03 15:09:25 by brivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_list_content_char(t_list **lst)
{
	t_list	*current;

	current = *lst;
	while (current != NULL)
	{
		if (current->content != NULL
			&& ft_strchr((char *)current->content, '='))
			printf("%s\n", (char *)current->content);
		current = current->next;
	}
}

/*
Su propósito es contar el número de caracteres
consecutivos al principio de la cadena s 
que están presentes en la cadena
*/
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

/*
La función recorre la cadena s buscando
el primer carácter que esté presente en reject.
*/
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

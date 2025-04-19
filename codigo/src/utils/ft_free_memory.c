/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_memory.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 12:24:52 by brivera           #+#    #+#             */
/*   Updated: 2025/04/19 19:12:37 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_free_ptr(void *ptr)
{
	if (ptr)
	{
		free(ptr);
		ptr = NULL;
	}
	return (NULL);
}

void	free_triple_array(char ***arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free_array(arr[i]);
		i++;
	}
	free(arr);
}

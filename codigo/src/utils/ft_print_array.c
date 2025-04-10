/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_array.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 16:50:19 by frivas            #+#    #+#             */
/*   Updated: 2025/04/10 12:35:44 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		printf("%s\n", array[i]);
		i++;
	}
}

void	ft_print_array_triple(char ***array)
{
	int	i;
	int	j;

	i = 0;
	while (array[i])
	{
		j = 0;
		while (array[i][j])
		{
			printf("%s\n", array[i][j]);
			j++;
		}
		i++;
	}
}

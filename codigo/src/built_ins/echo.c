/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 17:40:04 by frivas            #+#    #+#             */
/*   Updated: 2025/04/16 18:32:49 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_echo(char **command)
{
	int	i;

	i = 1;
	if (command[i][0] != '-')
	{
		while (command[i])
		{
			printf("%s", command[i]);
			if (command[i + 1])
				printf (" ");
			i++;
		}
		return (printf("\n"), 0);
	}
	else if (ft_strncmp(command[i], "-n", ft_strlen(command[i])))
		return (ft_putendl_fd(SUBJECTECHOOPTERROR, 2), 2);
	i = 2;
	while (command[i])
	{
		printf("%s", command[i]);
		if (command[i + 1])
			printf (" ");
		i++;
	}
	return (0);
}

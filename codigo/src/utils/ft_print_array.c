/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_array.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera@student.42madrid.com <brivera>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 16:50:19 by frivas            #+#    #+#             */
/*   Updated: 2025/05/03 19:36:28 by brivera@stu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		printf("array [%d] %s\n", i, array[i]);
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
			printf("ARRAY [%d][%d]: %s\n", i, j, array[i][j]);
			j++;
		}
		i++;
	}
}

void	ft_print_redir_array(t_redir **redir)
{
	int	i;
	int	j;

	if (!redir)
		return ;
	i = 0;
	while (redir[i])
	{
		j = 0;
		printf("  Redir #%d:\n", i);
		while (redir[i][j].type)
		{
			printf("    [%d][%d] Type: %s\n", i, j, redir[i][j].type);
			printf("    [%d][%d] Namefile: %s\n", i, j, redir[i][j].namefile);
			printf("    [%d][%d] FD: %d\n", i, j, redir[i][j].fd);
			//printf("    [%d][%d] FD[2]: %d\n", redir[i][j].fd_pipe);
			j++;
		}
		i++;
	}
}

void	ft_print_command_array(t_command *commands, int count)
{
	int	i;
	int	j;

	i = 0;
	while (i < count)
	{
		printf("Command #%d:\n", i);
		if (commands[i].command == NULL)
		{
			printf("  (null command)\n");
		}
		else
		{
			j = 0;
			while (commands[i].command[j])
			{
				printf("  Arg[%d]: %s\n", j, commands[i].command[j]);
				j++;
			}
		}
		i++;
	}
}

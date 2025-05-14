/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_array.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 16:50:19 by frivas            #+#    #+#             */
/*   Updated: 2025/05/14 17:18:49 by frivas           ###   ########.fr       */
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
			printf("  (null command)\n");
		else
		{
			j = 0;
			while (commands[i].command[j])
			{
				printf("  Comando[%d]: %s\n", j, commands[i].command[j]);
				j++;
			}
		}
		printf("  Input_name: %s\n", commands[i].input_name);
		printf("  Input_fd: %d\n", commands[i].fd_input);
		printf("  Output_name: %s\n", commands[i].output_name);
		printf("  Output_fd: %d\n", commands[i].fd_output);
		printf("  Output_type: %s\n", commands[i].type_output);
		i++;
	}
}

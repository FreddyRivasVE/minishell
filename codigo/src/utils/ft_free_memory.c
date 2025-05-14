/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_memory.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 12:24:52 by brivera           #+#    #+#             */
/*   Updated: 2025/05/14 17:19:30 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
ft_free_ptr - Libera memoria de forma segura y evita punteros colgantes.
Esta función toma un puntero a puntero (void **) y:
	- Verifica que el puntero no sea NULL.
	- Libera la memoria apuntada si existe.
	- Establece el puntero original a NULL.
Uso recomendado para prevenir errores de doble free o acceso a memoria liberada.
*/

void	ft_free_ptr(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

void	ft_free_triple_array(char ***arr)
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

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*joined;

	if (!s1 || !s2)
		return (NULL);
	joined = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (joined);
}

void	ft_free_redir_array(t_redir **redir)
{
	int	i;
	int	j;

	if (!redir)
		return ;
	i = 0;
	while (redir[i])
	{
		j = 0;
		while (redir[i][j].type != NULL || redir[i][j].namefile != NULL)
		{
			ft_free_ptr((void **)&redir[i][j].type);
			ft_free_ptr((void **)&redir[i][j].namefile);
			j++;
		}
		free(redir[i]);
		i++;
	}
	free(redir);
}

void	ft_free_command_array(t_command *commands, int count)
{
	int	i;
	int	j;

	if (!commands)
		return ;
	i = 0;
	while (i < count)
	{
		if (commands[i].command)
		{
			j = 0;
			while (commands[i].command[j])
			{
				free(commands[i].command[j]);
				j++;
			}
			free(commands[i].command);
		}
		ft_free_ptr((void **)&commands[i].input_name);
		ft_free_ptr((void **)&commands[i].output_name);
		ft_free_ptr((void **)&commands[i].type_output);
		i++;
	}
	free(commands);
}

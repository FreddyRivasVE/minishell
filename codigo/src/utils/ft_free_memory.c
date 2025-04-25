/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_memory.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera@student.42madrid.com <brivera>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 12:24:52 by brivera           #+#    #+#             */
/*   Updated: 2025/04/25 17:10:38 by brivera@stu      ###   ########.fr       */
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

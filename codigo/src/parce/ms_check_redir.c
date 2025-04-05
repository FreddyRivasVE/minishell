/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_check_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera@student.42madrid.com <brivera>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 15:40:59 by frivas            #+#    #+#             */
/*   Updated: 2025/04/05 20:08:31 by brivera@stu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Verifica si el carácter es un operador de redirección
*/
static bool	is_redirection_char(char c)
{
	return (c == '<' || c == '>');
}

/*
Verifica la validez de las redirecciones en un string
str String a analizar
return true si las redirecciones son válidas, false si hay errores
*/

bool	ms_check_redir(char *str)
{
	size_t	i;
	size_t	flag;
	bool	check_redir;

	check_redir = true;
	i = ft_strcspn(str, "<>");
	if (i < ft_strlen(str))
	{
		check_redir = false;
		flag = 1;
		i++;
	}
	while (str[i])
	{
		if (is_redirection_char(str[i]))
		{
			flag++;
			check_redir = false;
		}
		if (ft_isascii(str[i]) && !is_redirection_char(str[i]) && (flag < 3))
		{
			check_redir = true;
			flag = 0;
		}
		i++;
	}
	return (check_redir);
}

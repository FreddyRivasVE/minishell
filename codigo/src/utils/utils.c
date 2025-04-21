/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 12:33:49 by frivas            #+#    #+#             */
/*   Updated: 2025/04/21 17:13:56 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
funcion para limpiar espacios en los extremos
*/

char	*ft_strtrim_spaces(char *s)
{
	size_t	start;
	size_t	end;
	char	*res;

	if (!s)
		return (NULL);
	start = 0;
	end = ft_strlen(s);
	while (s[start] && ft_isspace(s[start]))
		start++;
	while (end > start && ft_isspace(s[end - 1]))
		end--;
	res = ft_substr(s, start, end - start);
	ft_free_ptr(s);
	return (res);
}

/*
Compara dos strings
0  si `s1` y `s2` son iguales.
<0 si `s1` es menor que `s2` (en orden ASCII).
>0 si `s1` es mayor que `s2`. 
Nota:`unsigned char` para manejar valores >127 correctamente.
 */
int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
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

size_t	ft_seek_lastc(char *str, char c)
{
	int	i;

	i = ft_strlen(str) - 1;
	while (str[i] && i >= 0)
	{
		if (str[i] == c)
			return (i);
		i--;
	}
	return (i);
}

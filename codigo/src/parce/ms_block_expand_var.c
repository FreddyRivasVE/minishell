/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_block_expand_var.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 15:08:09 by frivas            #+#    #+#             */
/*   Updated: 2025/05/19 20:20:04 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ms_build_new_string(char *str, char *new_str)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i])
	{
		while (str[i] != '\0' && !ft_isspace(str[i]))
		{
			new_str[j] = str[i];
			i++;
			j++;
		}
		if (ft_isspace(str[i]))
		{
			new_str[j] = '\"';
			j++;
		}
		while (str[i] != '\0' && ft_isspace(str[i]))
		{
			new_str[j] = str[i];
			j++;
			i++;
		}
		if (str[i] != '\0')
		{
			new_str[j] = '\"';
			j++;
		}
	}
	new_str[++j] = '\0';
}

static size_t	ft_count_newword(char const *s)
{
	size_t	count;
	size_t	i;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		while (ft_isspace(s[i]) && s[i] != '\0')
			i++;
		if (s[i] != '\0')
			count++;
		while (!ft_isspace(s[i]) && s[i] != '\0')
			i++;
	}
	return (count);
}

char	*ms_block_expand_var(char *expand, t_mshell *data)
{
	char	*res;
	int		new_len;

	new_len = ft_strlen(expand) + (ft_count_newword(expand) * 2);
	printf("new len: %d\n", new_len); //borrar
	res = ft_calloc(new_len + 1, sizeof(char));
	if (!res)
	{
		ms_print_perror_malloc(data);
		return (NULL);
	}
	ms_build_new_string(expand, res);
	ft_free_ptr((void **)&expand);
	printf("res: %s\n", res); //borrar
	return (res);
}

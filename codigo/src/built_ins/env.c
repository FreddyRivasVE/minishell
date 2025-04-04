/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera@student.42madrid.com <brivera>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 19:52:54 by brivera@stu       #+#    #+#             */
/*   Updated: 2025/04/04 21:43:57 by brivera@stu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//env sin opciones o argumentos
int	ms_env(char **command, t_list **lst)
{
	if (command[1])
	{
		ft_putendl_fd("env: subject doesn't allow arguments or options", 2);
		return (2);
	}
	print_list_content_char(lst);
	return (0);
}

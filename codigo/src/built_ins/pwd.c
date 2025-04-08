/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-08 14:35:24 by brivera           #+#    #+#             */
/*   Updated: 2025-04-08 14:35:24 by brivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_pwd(char **command)
{
	char	*pwd;

	if (command[1])
	{
		ft_putendl_fd("env: subject doesn't allow arguments or options", 2);
		return (2);
	}
	pwd = ms_get_cwd();
	if (!pwd)
	{
		ft_putendl_fd("pwd: error retrieving current directory", 2);
		return (1);
	}
	printf("%s\n", pwd);
	free(pwd);
	return (0);
}

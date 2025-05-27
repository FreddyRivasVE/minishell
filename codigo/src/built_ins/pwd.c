/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 14:35:24 by brivera           #+#    #+#             */
/*   Updated: 2025/04/21 15:36:26 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_pwd(char **command, t_list **env)
{
	char		*pwd;

	if (command[1])
	{
		ft_putendl_fd("env: subject doesn't allow arguments or options", 2);
		return (2);
	}
	pwd = ms_qd_kill(ft_list_extract_if(env, "PWD", var_cmp));
	if (!pwd)
		pwd = ms_get_cwd();
	if (!pwd)
	{
		ft_putendl_fd("pwd: error retrieving current directory", 2);
		return (1);
	}
	ft_putendl_fd(pwd, 1);
	free(pwd);
	return (0);
}

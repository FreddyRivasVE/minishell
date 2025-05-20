/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_01.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 16:00:35 by frivas            #+#    #+#             */
/*   Updated: 2025/05/20 16:10:23 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_update_pwd(char *newpwd, t_list **env)
{
	char	*pwdupdated;
	char	*temp;

	pwdupdated = ft_strjoin("PWD=", newpwd);
	temp = ms_add_dquotes(pwdupdated);
	ft_free_ptr((void **)&pwdupdated);
	pwdupdated = ft_strdup(temp);
	ft_free_ptr((void **)&temp);
	ft_list_replace_cont(env, ft_strdup(pwdupdated), var_cmp);
	ft_free_ptr((void **)&newpwd);
	ft_free_ptr((void **)&pwdupdated);
}

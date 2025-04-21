/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_get_cwd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 16:07:50 by frivas            #+#    #+#             */
/*   Updated: 2025/04/21 16:08:41 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ms_get_cwd(void)
{
	char	*rpwd;

	rpwd = getcwd(NULL, 0);
	if (!rpwd)
	{
		perror("getcwd");
		return (NULL);
	}
	return (rpwd);
}

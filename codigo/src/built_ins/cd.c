/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 14:40:32 by frivas            #+#    #+#             */
/*   Updated: 2025/04/01 13:58:42 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
como saca la shell el error
getcwd: cannot access parent directories: No such file or directory
*/

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

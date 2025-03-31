/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 14:40:32 by frivas            #+#    #+#             */
/*   Updated: 2025/03/31 17:27:03 by brivera          ###   ########.fr       */
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

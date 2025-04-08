/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera@student.42madrid.com <brivera>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 19:45:41 by brivera@stu       #+#    #+#             */
/*   Updated: 2025/04/08 21:32:09 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//sin opciones pero con argumentos
int	ms_exit(t_mshell *data)
{
	(void)*data;
	printf("exit\n");
	return (0);
}

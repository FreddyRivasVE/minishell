/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_structure.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 14:19:27 by frivas            #+#    #+#             */
/*   Updated: 2025/03/24 16:08:12 by brivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_STRUCT_H
# define MS_STRUCT_H

typedef struct s_pipe
{
}	t_pipe;

typedef struct s_redir
{
}	t_redir;

typedef struct s_comman
{
}	t_comman;

typedef struct s_exit
{
}	t_exit;

typedef struct s_input
{
}	t_input;

typedef struct s_mshell
{
	t_list  *env;
	t_pipe  *pipes;
	t_redir *redirs;
	t_comman *commands;
	t_exit  *exits;
	t_input *inputs;
}	t_mshell;

#endif

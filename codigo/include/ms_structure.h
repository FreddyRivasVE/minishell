/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_structure.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 14:19:27 by frivas            #+#    #+#             */
/*   Updated: 2025/03/26 17:09:19 by brivera          ###   ########.fr       */
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

typedef struct s_command
{
}	t_command;

typedef struct s_exit
{
}	t_exit;

typedef struct s_input
{
	char	*read_line;
}	t_input;

typedef struct s_mshell
{
	t_list  *env;
	t_pipe  *pipes;
	t_redir *redirs;
	t_command *commands;
	t_exit  *exits;
	t_input *inputs;
	char	*prompt;
}	t_mshell;

#endif

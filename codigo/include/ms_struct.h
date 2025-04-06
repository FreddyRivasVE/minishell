/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_struct.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 14:19:27 by frivas            #+#    #+#             */
/*   Updated: 2025/04/06 16:32:31 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_STRUCT_H
# define MS_STRUCT_H

typedef struct termios	t_term;

typedef struct s_redir
{
}	t_redir;

typedef struct s_pipe
{
}	t_pipe;

typedef struct s_command
{
}	t_command;

// typedef struct s_exit
// {
// 	char	*code;
// }	t_exit;

typedef struct s_input
{
	char	**splitpipes;
}	t_input;

typedef struct s_mshell
{
	t_list		*env;
	t_term		conftty;
	char		*input_row;
	t_pipe		*pipes;
	t_redir		*redirs;
	t_command	*commands;
	int			exits;
	t_input		*inputs;
	char		*prompt;
}	t_mshell;
#endif

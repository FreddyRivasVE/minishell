/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_struct.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera@student.42madrid.com <brivera>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 14:19:27 by frivas            #+#    #+#             */
/*   Updated: 2025/04/02 20:44:33 by brivera@stu      ###   ########.fr       */
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

typedef struct s_exit
{
	int	code;
}	t_exit;

typedef struct s_input
{
	char	*read_line;
}	t_input;

typedef struct s_mshell
{
	t_list		*env;
	t_term		conftty;
	char		*inputrow;
	t_pipe		*pipes;
	t_redir		*redirs;
	t_command	*commands;
	t_exit		*exits;
	t_input		*inputs;
	char		*prompt;
}	t_mshell;
#endif

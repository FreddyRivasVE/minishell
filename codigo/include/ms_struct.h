/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_struct.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera@student.42madrid.com <brivera>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 14:19:27 by frivas            #+#    #+#             */
/*   Updated: 2025/04/11 19:23:52 by brivera@stu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_STRUCT_H
# define MS_STRUCT_H

typedef struct termios	t_term;

typedef struct s_redir
{
	//char	*namefile;
	//int		fd;
}	t_redir;

typedef struct s_pipe
{
}	t_pipe;

typedef struct s_command
{
	//t_redir		redir;
	//char		**command;
}	t_command;

// typedef struct s_exit
// {
// 	char	*code;
// }	t_exit;

typedef struct s_input
{
	char	**splitpipes;
	char	***splitaftpipes;
}	t_input;

typedef struct s_mshell
{
	t_list		*env;
	t_term		conftty;
	char		*input_row;
	t_pipe		*pipes;
	t_command	*commands;
	int			exits;
	t_input		*inputs;
	char		*prompt;
}	t_mshell;
#endif

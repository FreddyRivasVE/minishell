/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_struct.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 14:19:27 by frivas            #+#    #+#             */
/*   Updated: 2025/05/05 17:18:28 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_STRUCT_H
# define MS_STRUCT_H

# define MODE_PROMPT   0
# define MODE_HEREDOC  1
# define MODE_CHILD    2

typedef struct termios	t_term;

/*typedef struct s_pipe
{
}	t_pipe;
*/

typedef struct s_redir
{
	char	*type;
	char	*namefile;
	int		fd;
	int		fd_pipe[2];
}	t_redir;

typedef struct s_command
{
	char	**command;
}	t_command;

// typedef struct s_exit
// {
// 	char	*code;
// }	t_exit;

typedef struct s_input
{
	char	**splitpipes;
	char	***splitaftpipes;
	char	**tag;
}	t_input;

typedef struct s_mshell
{
	t_list		*env;
	t_term		conftty;
	char		*input_row;
	//t_pipe		*pipes;
	t_command	*commands;
	t_redir		**redir;
	int			exits;
	t_input		*inputs;
	char		*prompt;
	int			pipesnum;
	int			mode;
}	t_mshell;
#endif

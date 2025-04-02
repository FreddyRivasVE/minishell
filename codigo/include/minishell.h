/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 10:52:52 by brivera           #+#    #+#             */
/*   Updated: 2025/04/02 16:45:12 by brivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdbool.h>
# include <limits.h>
# include <linux/limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <signal.h>
# include <stdio.h>
# include <unistd.h>
# include <termios.h>
# include "../libs/libft/libft.h"
# include "../include/ms_struct.h"

# define GREEN       "\033[92;1m"
# define CLEAR_COLOR "\033[0m"
# define CYAN        "\033[96;1m"

/*Es la forma que encontre de poder usar la variable en mac
la tengo que extraer explicitamente, seguro norminete te salta
al final se retira.*/
# ifdef __APPLE__

extern int	rl_catch_signals;
# endif

void	ms_sigctrlc_handler(int signo);
void	ms_init_struct(t_mshell *data, char **env);
void	print_list_content_char(t_list **lst);
void	ms_get_prompt(t_mshell *data);
void	ms_loop_minishell(t_mshell *data);
size_t	ft_strcspn(const char *s, const char *reject);
size_t	ft_strspn(const char *s, const char *accept);
char	*ms_get_cwd(void);
bool	ms_check_quotation_marks(char *str);
void	ms_input_row_validation(t_mshell *data);
bool	ms_check_pipes(char *str);
bool	ms_check_redir(char *str);

#endif

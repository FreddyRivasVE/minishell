/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 10:52:52 by brivera           #+#    #+#             */
/*   Updated: 2025/04/08 21:48:18 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdbool.h>
# include <limits.h>
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

# define GREEN			"\001\033[92;1m\002"
# define CLEAR_COLOR	"\001\033[0m\002"
# define CYAN			"\033[96;1m"

# define MINI_PRONT          "\001\033[92;1m\002minishell:$ \001\033[0m\002"

/*Este error indica: no hay
suficiente memoria disponible.*/
# define ENOMEM 12

/*Es la forma que encontre de poder usar la variable en mac
la tengo que extraer explicitamente, seguro norminete te salta
al final se retira.*/
# ifdef __APPLE__

extern int	rl_catch_signals;
# endif

void	ms_sigctrlc_handler(int signo);
void	ms_init_struct(t_mshell *data, char **env);
void	ms_loop_minishell(t_mshell *data);
void	ms_get_prompt(t_mshell *data);
bool	ms_check_quotation_marks(char *str);
bool	ms_check_pipes(char *str);
bool	ms_check_redir(char *str);
int		ms_input_row_validation(t_mshell *data);
int		ms_exec_builtin_or_other(char ***command, t_mshell *data, int i);
int		ms_split_input(t_mshell *data);
int		ms_exec(t_mshell *data);

/*****************************************************************************/
/*                                utils	                            		 */
/*****************************************************************************/

int		ft_isspace(int c);
size_t	ft_strcspn(const char *s, const char *reject);
size_t	ft_strspn(const char *s, const char *accept);
int		ft_strcmp(const char *s1, const char *s2);
void	*ms_free_ptr(void *ptr);
void	ft_print_array(char **array);
void	free_triple_array(char ***arr);

/*****************************************************************************/
/*                              BUILT-INS                           		 */
/*****************************************************************************/

char	*ms_get_cwd(void);
int		ms_export(char **command, t_mshell *data);
t_list	*ms_copy_export_env(t_list **env);
void	print_list_sorted(t_list **lst);
int		ms_env(char **command, t_list **lst);
int		ms_exit(t_mshell *data);
int		ms_unset(void);
int		ms_pwd(char **command);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 10:52:52 by brivera           #+#    #+#             */
/*   Updated: 2025/04/24 14:47:41 by frivas           ###   ########.fr       */
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
# include <sys/stat.h>
# include "../libs/libft/libft.h"
# include "../include/ms_struct.h"
# include "minisherror.h"

# define GREEN			"\001\033[92;1m\002"
# define CLEAR_COLOR	"\001\033[0m\002"
# define CYAN			"\033[96;1m"

# define MINI_PRONT          "\001\033[92;1m\002minishell:$ \001\033[0m\002"

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
void	ms_split_input(t_mshell *data);
int		ms_exec(t_mshell *data);
void	ms_expand_variable(t_mshell *data);
void	ms_quotes_killer(char ***inputs);
void	ms_pre_commands(t_mshell *data);

/*****************************************************************************/
/*                                utils	                            		 */
/*****************************************************************************/

int		ft_isspace(int c);
size_t	ft_strcspn(const char *s, const char *reject);
size_t	ft_strspn(const char *s, const char *accept);
int		ft_strcmp(const char *s1, const char *s2);
void	*ft_free_ptr(void *ptr);
void	ft_print_array(char **array);
void	free_triple_array(char ***arr);
void	ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)());
void	ft_print_array_triple(char ***array);
bool	toggle_simples(char c, bool check_simples, bool check_doubles);
bool	toggle_doubles(char c, bool check_simples, bool check_doubles);
char	**ft_split_quotes(char const *s, bool check);
char	**ft_split_pipes(char const *s);
char	*ft_strtrim_spaces(char *s);
char	*ft_list_extract_if(t_list **begin_list, void *data_ref, int (*cmp)());
char	*ft_escape_special_chars(char *input);
void	ms_update_prompt(t_mshell *data);
bool	special_char(int c);
size_t	ft_seek_lastc(char *str, char c);
void	ft_print_error(char *arg, char	*var, char *msj);
char	*ft_strjoin_free(char *s1, char *s2);

/*****************************************************************************/
/*                              BUILT-INS                           		 */
/*****************************************************************************/

int		ms_export(char **command, t_mshell *data);
int		ms_env(char **command, t_list **lst);
int		ms_exit(t_mshell *data);
int		ms_unset(t_mshell *data, char **data_ref);
int		ms_pwd(char **command, t_list **env);
int		ms_echo(char **command);
int		ms_cd(char	**s_command, t_list **env, t_mshell *data);
t_list	*ms_copy_export_env(t_list **env);
int		ms_export_print_list(t_list **env);
int		ft_list_replace_cont(t_list **begin_list, void *ref, int (*cmp)());
char	*ms_get_cwd(void);
int		var_cmp(void *data, void *ref);

#endif

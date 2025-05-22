/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 10:52:52 by brivera           #+#    #+#             */
/*   Updated: 2025/05/22 08:17:41 by brivera          ###   ########.fr       */
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
# include <sys/wait.h>
# include <sys/ioctl.h>
# include "../libs/libft/libft.h"
# include "../include/ms_struct.h"
# include "minisherror.h"

# define GREEN			"\001\033[92;1m\002"
# define CLEAR_COLOR	"\001\033[0m\002"
# define MINI_PRONT		"\001\033[92;1m\002minishell:$ \001\033[0m\002"

extern int	g_signal;

# ifdef __APPLE__

extern int	rl_catch_signals;
# endif 

/*****************************************************************************/
/*                              shell init                            		 */
/*****************************************************************************/

void	ms_get_prompt(t_mshell *data);
void	ms_init_struct(t_mshell *data, char **env);
void	ms_loop_minishell(t_mshell *data);
void	ms_set_signal_handler(int mode);
void	reset_terminal_settings(void);

/*****************************************************************************/
/*                             		parce                            		 */
/*****************************************************************************/

int		ms_input_row_validation(t_mshell *data);
int		ms_orquest_command(t_mshell *data, char ***split, char **tag);
bool	ms_check_pipes(char *str);
bool	ms_check_quotation_marks(char *str);
bool	ms_check_redir(char *str);
bool	ms_quotes_killer(char ***inputs, t_mshell *data);
bool	ms_redir_together(t_mshell *data);
bool	ms_split_input(t_mshell *data);
bool	ms_token_input(t_mshell *data);
bool	ms_orquest(t_mshell *data, char ***split, char **tag);
char	*ms_escape_special_chars(char *str);
char	*ms_expand_child(char *str, t_mshell *data);
char	*ms_block_expand_var(char *expand, t_mshell *data);
bool	ms_special_expand(t_mshell *data);
bool	ms_reserve_memory_redir(char *str, t_mshell *data);
bool	ms_control_expand_heredoc(char *str, int pos, t_mshell *data);
bool	ms_has_leading_pipe(char *str);

/*****************************************************************************/
/*                             	execution                           		 */
/*****************************************************************************/

int		ms_exec_builtin_or_other(char **command, t_mshell *data);
int		ms_exec_other(char **command, t_mshell *data);
bool	ms_redir_management(t_mshell *data);
bool	ms_heredoc_management(t_mshell *data);
char	*ms_recoverpath(char *commands, t_list **env, t_mshell *data);
void	ms_exec(t_mshell *data);
void	ms_execute_command(char *path, char **command, char **envp);
void	ms_simple_execution(t_mshell *data);
void	run_pipeline(t_command *cmds, int total, t_mshell *data);
void	ms_free_child(char *msm, t_mshell *data, int flag);
void	ms_free_command_child(char **command, t_mshell *data, char *msm);
void	ms_redirect_child_input(t_command *cmds, int i, t_mshell *data);
void	ms_redirect_child_output(t_command *cmds, int i, int total, \
		t_mshell *data);
void	ms_move_env_to_pointer(t_mshell *data);

/*****************************************************************************/
/*                              BUILT-INS                           		 */
/*****************************************************************************/

int		ms_export(char **command, t_mshell *data);
int		ms_export_print_list(t_list **env);
int		ms_env(char **command, t_list **lst);
int		ms_exit(char **command, t_mshell *data);
int		ms_unset(t_mshell *data, char **data_ref);
int		ms_pwd(char **command, t_list **env);
int		ms_echo(char **command);
int		ms_cd(char	**s_command, t_list **env, t_mshell *data);
void	ms_update_pwd(char *newpwd, t_list **env);

/*****************************************************************************/
/*                                utils	                            		 */
/*****************************************************************************/

int		ft_isspace(int c);
int		ft_list_replace_cont(t_list **begin_list, void *ref, int (*cmp)());
int		ft_strcmp(const char *s1, const char *s2);
int		var_cmp(void *data, void *ref);
size_t	ft_seek_lastc(char *str, char c);
size_t	ft_strcspn(const char *s, const char *reject);
size_t	ft_strspn(const char *s, const char *accept);
bool	ft_special_char(int c);
bool	ms_is_quoted_redirection(char *s);
bool	toggle_doubles(char c, bool check_simples, bool check_doubles);
bool	toggle_simples(char c, bool check_simples, bool check_doubles);
bool	ft_isredirection_char(char c);
char	**ft_split_pipes(char const *s);
char	**ft_split_quotes(char const *s, bool check);
char	*ft_strjoin_free(char *s1, char *s2);
char	*ft_strtrim_spaces(char *s);
char	*ft_list_extract_if(t_list **begin_list, void *data_ref, int (*cmp)());
char	*ms_get_cwd(void);
char	*ms_add_dquotes(char *str);
char	*ms_qd_kill(char *str);
t_list	*ms_copy_export_env(t_list **env);
void	ft_close_heredoc_fds(t_mshell *data);
void	ft_free_ptr(void **ptr);
void	ft_free_triple_array(char ***arr);
void	ft_free_redir_array(t_redir **redir);
void	ft_free_command_array(t_command *commands, int count);
void	ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)());
void	ft_print_array(char **array);
void	ft_print_array_triple(char ***array);
void	ft_print_error(char *arg, char *var, char *msj);
void	ft_print_redir_array(t_redir **redir);
void	ft_print_command_array(t_command *commands, int count);
void	ms_exit_minishell(t_mshell *data);
void	ms_print_perror_malloc(t_mshell *data);
void	ms_print_perror_exit(char *str, int num);
void	ms_update_prompt(t_mshell *data);
#endif

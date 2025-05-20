/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_init_struct.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 14:16:48 by frivas            #+#    #+#             */
/*   Updated: 2025/05/20 16:13:42 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ms_get_ttyinfo(t_mshell *data)
{
	if (isatty(STDIN_FILENO))
		tcgetattr(STDIN_FILENO, &data->conftty);
}

static char	*ft_getnstr(char *str, char *c)
{
	char	*nstr;
	int		len;

	len = ft_strlen(str);
	nstr = ft_substr(str, ft_strcspn(str, c) + 1, len);
	if (!nstr)
		return (NULL);
	return (nstr);
}

static char	*ms_get_env_line(char	*env)
{
	char	*env_line;
	char	*level;
	char	*temp;

	if (!ft_strncmp("SHLVL=", env, 6))
	{
		temp = ft_getnstr(env, "=");
		if (!temp)
			return (NULL);
		level = ft_itoa(ft_atoi(temp) + 1);
		free(temp);
		if (!level)
			return (NULL);
		if (level[0] == '-')
		{
			free(level);
			level = ft_strdup("0");
		}
		env_line = ft_strjoin_free(ft_strdup("SHLVL="), level);
	}
	else
		env_line = ft_strdup(env);
	temp = ms_add_dquotes(env_line);
	free(env_line);
	return (temp);
}

static t_list	*ms_get_env(char **env)
{
	int		i;
	char	*envread;
	t_list	*new_node;
	t_list	*env_list;

	i = 0;
	env_list = NULL;
	while (env[i])
	{
		envread = ms_get_env_line(env[i]);
		if (!envread)
			break ;
		new_node = ft_lstnew(envread);
		if (!new_node)
		{
			perror(ERRORCREATENODO);
			free(envread);
			ft_lstclear(&env_list, free);
		}
		ft_lstadd_back(&env_list, new_node);
		i++;
	}
	return (env_list);
}

void	ms_init_struct(t_mshell *data, char **env)
{
	t_list	*mini_env;

	rl_catch_signals = 0;
	data->commands = 0;
	data->exits = 0;
	data->inputs = 0;
	data->flag = 0;
	data->env = 0;
	data->pipesnum = 0;
	data->inistdin = 0;
	data->inistdout = 0;
	mini_env = ms_get_env(env);
	if (!mini_env)
		ft_lstclear(&mini_env, free);
	data->env = mini_env;
	ms_get_prompt(data);
	ms_get_ttyinfo(data);
}

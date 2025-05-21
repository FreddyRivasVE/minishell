/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_execution_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 11:51:22 by brivera           #+#    #+#             */
/*   Updated: 2025/05/14 18:23:58 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ms_kill_dquotes_v2(char *str)
{
	char	*result;
	int		i;
	int		j;
	int		flag;

	flag = 0;
	result = ft_calloc(ft_strlen(str), sizeof(char));
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i] != 0)
	{
		if (str[i] == '\"' && str[i + 1] == '\0')
			break ;
		result[j] = str[i];
		if (str[i] == '=' && flag == 0)
		{
			i++;
			flag = 1;
		}
		i++;
		j++;
	}
	return (result);
}

void	ms_move_env_to_pointer(t_mshell *data)
{
	int		count;
	t_list	*lst;
	int		i;

	i = 0;
	count = ft_lstsize(data->env);
	data->envp = ft_calloc(count + 1, sizeof(char *));
	if (!data->envp)
	{
		ms_print_perror_malloc(data);
		return ;
	}
	lst = data->env;
	while (lst != NULL)
	{
		data->envp[i] = ms_kill_dquotes_v2(lst->content);
		if (!data->envp[i])
		{
			ms_print_perror_malloc(data);
			free_array(data->envp);
			return ;
		}
		i++;
		lst = lst->next;
	}
}

static char	**ms_split_path(t_list **env, t_mshell *data)
{
	char	*path;
	char	**split_path;

	path = ft_list_extract_if(env, "PATH", var_cmp);
	if (!path)
		return (NULL);
	split_path = ft_split(path, ':');
	if (!split_path)
	{
		ms_print_perror_malloc(data);
		ft_free_ptr((void **)&path);
		return (NULL);
	}
	ft_free_ptr((void **)&path);
	return (split_path);
}

char	*ms_recoverpath(char *commands, t_list **env, t_mshell *data)
{
	int		i;
	char	**paths;
	char	*path;
	char	*part_path;

	paths = ms_split_path(env, data);
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, commands);
		if (!path)
			return (ms_print_perror_malloc(data), NULL);
		if (access(path, F_OK | X_OK) == 0)
			return (free_array(paths), path);
		ft_free_ptr((void **)&path);
		ft_free_ptr((void **)&part_path);
		i++;
	}
	return (free_array(paths), NULL);
}

void	ms_execute_command(char *path, char **command, char **envp)
{
	if (execve(path, command, envp) == -1)
		ms_print_perror_exit(command[0], 127);
	free_array(envp);
	exit(0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 14:40:32 by frivas            #+#    #+#             */
/*   Updated: 2025/05/05 13:14:35 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ms_expand_tilde(char *command, t_list **env)
{
	char	*home;
	char	*expanded;

	if (!command || command[0] != '~')
		return (ft_strdup(command));
	home = ft_list_extract_if(env, "HOME", var_cmp);
	if (!home)
		return (ft_putendl_fd("cd: HOME not set", 2), NULL);
	if (command[1] == '\0')
		return (home);
	if (command[1] == '/')
	{
		expanded = ft_strjoin(home, command + 1);
		free(home);
		return (expanded);
	}
	free(home);
	return (ft_strdup(command));
}

char	*ms_obtain_target(char **command, t_list **env, char *pwd)
{
	char	*target;

	target = NULL;
	if (!command[1] || ft_strcmp(command[1], "~") == 0
		|| ft_strcmp(command[1], "--") == 0)
	{
		target = ft_list_extract_if(env, "HOME", var_cmp);
		if (!target)
			return (ft_putendl_fd("cd: HOME not set", 2), NULL);
		return (target);
	}
	else if (ft_strcmp(command[1], "-") == 0)
	{
		target = ft_list_extract_if(env, "OLDPWD", var_cmp);
		if (!target || !pwd)
			return (ft_free_ptr((void **)&target), \
				ft_putendl_fd("cd: OLDPWD not set", 2), NULL);
		printf("%s\n", target);
		return (target);
	}
	else
	{
		target = ms_expand_tilde(command[1], env);
		return (target);
	}
}

void	ms_update_env_cd(char *oldpwd, char *newpwd, t_list **env)
{
	char	*newoldpwd;
	char	*pwdupdated;

	if (!oldpwd)
		ft_list_replace_cont(env, "OLDPWD=", var_cmp);
	else
	{
		newoldpwd = ft_strjoin("OLDPWD=", oldpwd);
		ft_list_replace_cont(env, newoldpwd, var_cmp);
	}
	pwdupdated = ft_strjoin("PWD=", newpwd);
	ft_list_replace_cont(env, pwdupdated, var_cmp);
}

void	ms_backup_pwd(char *oldpwd, t_list **env)
{
	char	*tempwd;

	tempwd = ft_strdup(oldpwd);
	while (1)
	{
		if (access(tempwd, F_OK))
		{
			ms_update_env_cd(oldpwd, tempwd, env);
			break ;
		}
		tempwd = ft_substr(tempwd, 0, (ft_strlen(tempwd) \
		- ft_seek_lastc(tempwd, '/')));
	}
}

int	ms_cd(char	**command, t_list **env, t_mshell *data)
{
	char	*oldpwd;
	char	*target;
	char	*newpwd;
	bool	flag;

	flag = false;
	oldpwd = ft_list_extract_if(env, "PWD", var_cmp);
	target = ms_obtain_target(command, env, oldpwd);
	if (!target)
		return (free(oldpwd), 1);
	if (chdir(target) != 0)
		return (perror("cd"), free(oldpwd), ft_free_ptr((void **)&target), 1);
	newpwd = ms_get_cwd();
	if (!newpwd)
	{
		if (flag)
			ms_backup_pwd(oldpwd, env);
		flag = true;
		ft_putendl_fd("cd: error retrieving current directory:", 2);
	}
	else
		ms_update_env_cd(oldpwd, newpwd, env);
	ms_update_prompt(data);
	return (ft_free_ptr((void **)&oldpwd), ft_free_ptr((void **)&newpwd), \
	ft_free_ptr((void **)&target), 0);
}

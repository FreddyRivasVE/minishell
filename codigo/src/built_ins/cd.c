/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera@student.42madrid.com <brivera>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 14:40:32 by frivas            #+#    #+#             */
/*   Updated: 2025/04/20 14:25:32 by brivera@stu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
como saca la shell el error
getcwd: cannot access parent directories: No such file or directory
*/

char	*ms_get_cwd(void)
{
	char	*rpwd;

	rpwd = getcwd(NULL, 0);
	if (!rpwd)
	{
		perror("getcwd");
		return (NULL);
	}
	return (rpwd);
}

char	*ms_expand_tilde(char *command, t_list **env)
{
	char	*home;
//	size_t	home_len;
//	size_t	suffix_len;
	char	*expanded;

	if (!command || command[0] != '~')
		return (command);
	home = ft_list_extract_if(env, "HOME", var_cmp);
	if (!home)
		return (ft_putendl_fd("cd: HOME not set\n", 2), NULL);
	if (command[1] == '\0')
		return (home);
	if (command[1] == '/')
	{
//		home_len = ft_strlen(home);
//		suffix_len = ft_strlen(command + 1);
		expanded = ft_strjoin(home, command + 1);
		free(home);
		return (expanded);
	}
	free(home);
	return (command);
}

char	*ms_obtain_target(char **command, t_list **env, char *oldpwd)
{
	char	*target;

	target = NULL;
	if (!command[1] || ft_strcmp(command[1], "~") == 0)
	{
		target = ft_list_extract_if(env, "HOME", var_cmp);
		if (!target)
			return (ft_putendl_fd("cd: HOME not set\n", 2), NULL);
		return (target);
	}
	else if (ft_strcmp(command[1], "-") == 0)
	{
		target = ft_strdup(oldpwd);
		if (!target)
			return (ft_putendl_fd("cd: OLDPWD not set\n", 2), NULL);
		printf("%s\n", target); //borrar
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
//	free(oldpwd);
	pwdupdated = ft_strjoin("PWD=", newpwd);
	ft_list_replace_cont(env, pwdupdated, var_cmp);
//	free(newpwd);
}

int	ms_cd(char	**command, t_list **env, t_mshell *data)
{
	char	*oldpwd;
	char	*target;
	char	*newpwd;

	oldpwd = ft_list_extract_if(env, "PWD", var_cmp);
	target = ms_obtain_target(command, env, oldpwd);
	if (chdir(target) != 0)
	{
		perror("cd");
		free(oldpwd);
		free(target);
		return (1);
	}
	newpwd = ms_get_cwd();
	ms_update_env_cd(oldpwd, newpwd, env);
	ft_free_ptr(oldpwd);
	ft_free_ptr(newpwd);
	ft_free_ptr(target);
	ms_update_prompt(data);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_update_prompt.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:41:46 by frivas            #+#    #+#             */
/*   Updated: 2025/05/20 15:18:33 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ms_update_host(void)
{
	char	*res;
	int		fd;
	int		end;
	int		bytes_read;
	char	*temp;

	fd = open("/etc/hostname", O_RDONLY);
	if (fd == -1)
		res = ft_strjoin("", "hostname");
	else
	{
		temp = ft_calloc(1024, sizeof(char));
		bytes_read = read(fd, temp, 1024);
		if (bytes_read == -1)
		{
			res = ft_strjoin("", "hostname");
			return (res);
		}
		end = ft_strcspn(temp, ".-\n");
		res = ft_substr(temp, 0, end);
		free(temp);
	}
	close(fd);
	return (res);
}

char	*ms_update_dir(t_mshell *data)
{
	char	*dir;
	char	*home;
	int		start;
	int		lenhom;
	char	*temp;

	home = ms_qd_kill(ft_list_extract_if(&data->env, "HOME", var_cmp));
	dir = ms_qd_kill(ft_list_extract_if(&data->env, "PWD", var_cmp));
	if (!home)
	{
		if (!dir)
			dir = ms_get_cwd();
		return (dir);
	}
	lenhom = ft_strlen(home);
	if (!dir)
		dir = ms_get_cwd();
	start = ft_strspn(home, dir);
	if (start >= lenhom)
	{
		temp = ft_substr(dir, start, (ft_strlen(dir) - start));
		ft_free_ptr((void **)&dir);
		dir = ft_strjoin_free(ft_strdup("~"), temp);
	}
	return (ft_free_ptr((void **)&home), dir);
}

void	ms_update_prompt(t_mshell *data)
{
	char	*hostn;
	char	*pwdir;
	char	*temp1;
	char	*temp2;

	hostn = ms_update_host();
	pwdir = ms_update_dir(data);
	if (!pwdir)
		pwdir = ft_strdup("");
	temp1 = ft_strjoin(GREEN, "minishell@");
	temp2 = ft_strjoin(temp1, hostn);
	ft_free_ptr((void **)&temp1);
	temp1 = ft_strjoin(temp2, ":");
	ft_free_ptr((void **)&temp2);
	temp2 = ft_strjoin(temp1, pwdir);
	ft_free_ptr((void **)&temp1);
	temp1 = ft_strjoin(temp2, "$ ");
	ft_free_ptr((void **)&temp2);
	free(data->prompt);
	data->prompt = ft_strjoin(temp1, CLEAR_COLOR);
	if (!data->prompt)
		data->prompt = MINI_PRONT;
	ft_free_ptr((void **)&temp1);
	ft_free_ptr((void **)&pwdir);
	ft_free_ptr((void **)&hostn);
}

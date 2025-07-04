/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_get_prompt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera@student.42madrid.com <brivera>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:41:46 by frivas            #+#    #+#             */
/*   Updated: 2025/04/25 17:07:37 by brivera@stu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ms_get_host(void)
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

static char	*ms_get_home(void)
{
	char	*temp;

	temp = getenv("HOME");
	if (!temp)
		return (NULL);
	return (temp);
}

char	*ms_get_dir(void)
{
	char	*dir;
	char	*home;
	int		start;
	int		lenhom;

	home = ms_get_home();
	if (!home)
		return (ms_get_cwd());
	dir = ft_strdup(getenv("PWD"));
	if (!dir)
		dir = ms_get_cwd();
	if (!dir)
		return (ft_putendl_fd(INITDIRWRONG, 2), NULL);
	lenhom = ft_strlen(home);
	start = ft_strspn(home, dir);
	if (start >= lenhom)
	{
		home = ft_substr(dir, start, (ft_strlen(dir) - start));
		free(dir);
		dir = ft_strjoin("~", home);
		free(home);
	}
	return (dir);
}

void	ms_get_prompt(t_mshell *data)
{
	char	*hostn;
	char	*pwdir;
	char	*temp1;
	char	*temp2;

	hostn = ms_get_host();
	pwdir = ms_get_dir();
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
	data->prompt = ft_strjoin(temp1, CLEAR_COLOR);
	if (!data->prompt)
		data->prompt = ft_strdup(MINI_PRONT);
	ft_free_ptr((void **)&temp1);
	ft_free_ptr((void **)&pwdir);
	ft_free_ptr((void **)&hostn);
}

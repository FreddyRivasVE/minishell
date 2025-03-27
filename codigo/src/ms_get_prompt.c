/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_get_prompt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:41:46 by frivas            #+#    #+#             */
/*   Updated: 2025/03/27 15:37:49 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_strspn(const char *s, const char *accept)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (ft_strchr(accept, s[i]) == 0)
			break ;
		++i;
	}
	return (i);
}

size_t	ft_strcspn(const char *s, const char *reject)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (s[i] != '\0')
	{
		while (reject[k] != '\0')
		{
			if (s[i] == reject[k])
				return (i);
			k++;
		}
		k = 0;
		i++;
	}
	return (i);
}

char	*ms_get_host(void)
{
	char	*res;
	int		fd;
	int		end;
	int		bytes_read;

	fd = open("/etc/hostname", O_RDONLY);
	if (fd == -1)
		res = ft_strjoin("", "hostname");
	else
	{
		res = ft_calloc(1024, sizeof(char));
		bytes_read = read(fd, res, 1024);
		if (bytes_read == -1)
		{
			res = ft_strjoin("", "hostname");
			return (res);
		}
		end = ft_strcspn(res, ".-\n");
		res = ft_substr(res, 0, end);
	}
	close(fd);
	return (res);
}

char	*ms_get_dir(void)
{
	char	*res;
	char	*temp;
	int		start;
	int		lenhom;

	temp = getenv("HOME");
	if (!temp)
	{
		res = getenv("PWD");
		return (res);
	}
	else
	{
		res = getenv("PWD");
		lenhom = ft_strlen(temp);
		start = ft_strspn(temp, res);
		if (start >= lenhom)
		{
			temp = ft_substr(res, start, (ft_strlen(res) - start));
			res = ft_strjoin("~", temp);
			free(temp);
		}
	}
	return (res);
}

void	ms_get_prompt(t_mshell *data)
{
	char	*hostn;
	char	*pwdir;
	char	*temp1;
	char	*temp2;
	char	*temp3;

	hostn = ms_get_host();
	pwdir = ms_get_dir();
	temp1 = ft_strjoin(GREEN, "minishell@");
	temp2 = ft_strjoin(temp1, hostn);
	free(temp1);
	temp1 = ft_strjoin(temp2, ":");
	free(temp2);
	temp2 = ft_strjoin(temp1, pwdir);
	free(temp1);
	temp1 = ft_strjoin(temp2, "$");
	free(temp2);
	temp3 = ft_strjoin(temp1, CLEAR_COLOR);
	free(temp1);
	data->prompt = temp3;
	free(temp3);
	if (getenv("HOME")
		&& (ft_strlen(getenv("PWD")) > ft_strlen(getenv("HOME"))))
		free(pwdir);
	free(hostn);
}

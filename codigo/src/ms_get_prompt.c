/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_get_prompt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:41:46 by frivas            #+#    #+#             */
/*   Updated: 2025/03/27 11:38:25 by brivera          ###   ########.fr       */
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
	//int		bytes_read; No es requerida debido a que usaremos read directamente en la linea 63.
	fd = open("/etc/hostname", O_RDONLY);
	if (fd == -1)
		res = ft_strjoin("", "hostname");
	else
	{
		res = ft_calloc(1024, sizeof(char));
		//bytes_read = read(fd, res, 1024);
		read(fd, res, 1024);
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
		//printf("%ilenhom\n", lenhom);
		start = ft_strspn(temp, res);
		//printf("%i\n", start);
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
	char	*temp;

	hostn = ms_get_host();
	pwdir = ms_get_dir();
	temp = ft_strjoin(GREEN, "minishell@");
	temp = ft_strjoin(temp, hostn);
	temp = ft_strjoin(temp, CLEAR_COLOR);
	temp = ft_strjoin(temp, ":");
	temp = ft_strjoin(temp, pwdir);
	data->prompt = ft_strjoin(temp, "$");
	printf("%s\n", data->prompt);
	free(temp);
	if (ft_strlen(getenv("PWD")) > ft_strlen(getenv("HOME")))
		free(pwdir);
	free(hostn);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_get_pront.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:41:46 by frivas            #+#    #+#             */
/*   Updated: 2025/03/26 15:49:31 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_strspn(const char *s, const char *accept)
{
	size_t i = 0;

	while (s[i] != '\0')
	{
		if (ft_strchr(accept, s[i]) == 0)
			break;
		++i;
	}
	return (i);
}

size_t	ft_strcspn(const char *s, const char *reject)
{
	int		i;
	int		k;
	
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

char    *ms_get_host(void)
{
	char    *res;
	int		fd;
	int		bytes_read;
	int		end;
	
	fd = open("/etc/hostname", O_RDONLY);
	if (fd == -1)
		res = ft_strjoin("", "hostname");
	else
	{
		res = (char *)malloc(sizeof(char) * 1024);
		bytes_read = read(fd, res, 1024);
		end = ft_strcspn(res, ".-");
		res = ft_substr(res, 0, end);
	}
	return (res);		
}

char	*ms_get_dir()
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
		start = ft_strspn(res, temp) - 1;
		if (start >= lenhom)
		{
			temp = ft_substr(res, start, (ft_strlen(res) - start));
			res = ft_strjoin("~/", temp);
			free(temp);
		}			
	}
	return (res);	
}

void    ms_get_pront(t_mshell *data)
{
	char    *hostn;
	char    *pwdir;
	char	*temp;
	
	hostn = ms_get_host();
	pwdir = ms_get_dir();
	temp = ft_strjoin("minishell@", hostn);
	temp = ft_strjoin(temp, ":");
	temp = ft_strjoin(temp, pwdir);	
	data->pront = ft_strjoin(temp, "$");
	printf("%s", data->pront);
	free(temp);
	if (ft_strlen(getenv("PWD")) > ft_strlen(getenv("HOME")))
		free(pwdir);
	free(hostn);	
}

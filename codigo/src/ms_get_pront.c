/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_get_pront.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:41:46 by frivas            #+#    #+#             */
/*   Updated: 2025/03/26 12:32:12 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	char	*temp;
	int		bytes_read;
	int		end;
	
	temp = (char *)malloc(sizeof(char) * 1024);
	fd = open("/etc/hostname", O_RDONLY);
	if (fd == -1)
		res = "hostname";
	else
		bytes_read = read(fd, temp, 1024);
	end = ft_strcspn(temp, ".-");
	res = ft_substr(temp, 0, end);
	free(temp);
	return (res);		
}

/*char	*ms_get_dir(char *str)
{
}*/


void    ms_get_pront(t_mshell **data)
{
	char    *hostn;
	char    *pwdir;
	(void)	data;

	hostn = ms_get_host();
	pwdir = getenv("PWD");
	//temp = ms_get_dir(temp);
	printf("%s\n", hostn);    
}

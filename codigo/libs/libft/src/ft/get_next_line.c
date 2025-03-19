/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera@student.42madrid.com <brivera>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 15:08:58 by brivera           #+#    #+#             */
/*   Updated: 2025/01/21 16:13:45 by brivera@stu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*readmyfd(char *texread, int fd)
{
	ssize_t	bytesread;
	char	*readline;
	char	*temp;

	readline = (char *)ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!readline)
		return (NULL);
	bytesread = 1;
	while (!ft_strchr(texread, '\n') && bytesread > 0)
	{
		bytesread = read(fd, readline, BUFFER_SIZE);
		if (bytesread < 0)
			return (free(readline), free(texread), NULL);
		if (bytesread == 0)
			break ;
		readline[bytesread] = '\0';
		temp = texread;
		texread = ft_strjoin(temp, readline);
		free(temp);
		if (!texread)
			return (NULL);
	}
	free(readline);
	return (texread);
}

char	*createmyline(char *texread)
{
	char	*createxread;
	int		i;
	int		j;

	i = 0;
	if (!texread)
		return (NULL);
	while (texread[i] && texread[i] != '\n')
		i++;
	if (texread[i] == '\n')
		i++;
	createxread = (char *)ft_calloc(i + 1, sizeof(char));
	if (!createxread)
		return (NULL);
	j = 0;
	while (j < i)
	{
		createxread[j] = texread[j];
		j++;
	}
	return (createxread);
}

char	*update_texread(char *texread)
{
	size_t	i;
	size_t	j;
	char	*myupdate;
	size_t	len;
	size_t	total_len;

	i = 0;
	j = 0;
	if (!texread)
		return (NULL);
	len = ft_strlen(texread);
	while (texread[i] != '\0' && texread[i] != '\n')
		i++;
	if ((len - i) == 0)
		return (free(texread), NULL);
	myupdate = ft_calloc((ft_strlen(texread) - i + 1), sizeof(char));
	if (!myupdate)
		return (NULL);
	total_len = len - i;
	while (j < total_len)
		myupdate[j++] = texread[++i];
	free(texread);
	return (myupdate);
}

char	*freefree(char *texread, char *texread_print)
{
	free(texread_print);
	free(texread);
	texread_print = NULL;
	texread = NULL;
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char			*texread;
	char				*texread_print;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!texread)
	{
		texread = ft_calloc(1, sizeof(char));
		if (!texread)
			return (NULL);
	}
	texread = readmyfd(texread, fd);
	if (!texread)
		return (NULL);
	texread_print = createmyline(texread);
	if (!texread_print)
		return (free(texread), texread = NULL, NULL);
	texread = update_texread(texread);
	if (texread_print && *texread_print == '\0')
		texread_print = freefree(texread, texread_print);
	return (texread_print);
}

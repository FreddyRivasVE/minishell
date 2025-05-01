/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_orquest.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera@student.42madrid.com <brivera>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:57:44 by frivas            #+#    #+#             */
/*   Updated: 2025/05/01 12:23:22 by brivera@stu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ms_check_redir_access(char *tag, char *file_name)
{
	if (!file_name)
		return (-1);
	if (!ft_strcmp(tag, "INPUT") && access(file_name, R_OK) == -1)
		return (-1);
	if (!ft_strcmp(tag, "OUTPUT")
		&& access(file_name, F_OK | W_OK) == -1)
		return (-1);
	if (!ft_strcmp(tag, "OUTPUTAPPEND")
		&& access(file_name, F_OK | W_OK | R_OK) == -1)
		return (-1);
	return (0);
}

static int	ms_is_redirection(char *tag)
{
	return (!ft_strcmp(tag, "HEREDOC")
		|| !ft_strcmp(tag, "OUTPUTAPPEND")
		|| !ft_strcmp(tag, "INPUT")
		|| !ft_strcmp(tag, "OUTPUT" ));
}

static bool	ms_fill_commands(char *tag, char *split, t_mshell *data, int i, int l)
{
	data->redir[i][l].type = ft_strdup(tag);
	data->redir[i][l].namefile = ft_strdup(split);
	if (!data->redir[i][l].type)
		return (ms_print_perror_malloc(data), false);
	printf("redir estructura: %d --- lado del pipe: %d --- valor guardado type:%s name: %s", i, l, data->redir[i][l].type, data->redir[i][l].namefile); //borrar
	return (true);
}

static bool	ms_reserve_memory_redir(char *str, t_mshell *data)
{
	int	i;
	int	i_r;
	int	num_redir;

	i = 0;
	i_r = 0;
	while (str[i])
	{
		num_redir = 0;
		printf("valores de i %d y num redir%d ", i, num_redir); //borrar
		while (str[i] && str[i] != '|')
		{
			if (ft_isredirection_char(str[i]))
			{
				if (ft_isredirection_char(str[i + 1]))
					i++;
				num_redir++;
			}
			i++;
		}
		data->redir[i_r] = ft_calloc(num_redir + 1, sizeof(t_redir));
		if (!data->redir[i_r])
			return (ms_print_perror_malloc(data), false);
		i_r++;
		i++;
	}
	return (true);
}

static bool	ms_orquest_redir(t_mshell *data, char ***split, char **tag)
{
	int		i;
	int		j;
	int		k;
	bool	flag;
	int 	l;

	i = -1;
	k = 0;
	while (split[++i])
	{
		flag = false;
		j = 0;
		l = 0;
		printf("valores de i %d y j %d ", i, j); //borrar
		while (split[i][j])
		{
			if (ms_is_redirection(tag[k]) && !flag)
			{
				if (!ms_fill_commands(tag[k], split[i][j + 1], data, i, l))
					return (false);
				if (ms_check_redir_access(tag[k], split[i][j + 1]) == -1)
					flag = true;
				l++;
			}
			j++;
			k++;
		}
	}
	return (true);
}

bool	ms_orquest(t_mshell *data, char ***split, char **tag)
{
	printf("entramos a orquest\n"); //borrar
	if (!ms_reserve_memory_redir(data->input_row, data))
		return (false);
	if (!ms_orquest_redir(data, split, tag))
		return (false);
	if (ms_orquest_command(data, split, tag) == -1)
		return (false);
	return (true);
}

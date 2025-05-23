/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_loop_minishell_nointeractive.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 14:30:06 by frivas            #+#    #+#             */
/*   Updated: 2025/05/23 15:26:45 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	copy_segments(char *result, const char *src, int pos)
{
	size_t	src_len;

	src_len = strlen(src);
	ft_memmove(result, src, pos);
	ft_memmove(result + pos, "\0", 1);
}

static char	*ms_clean_cmd(char *cmd_row, char *seek)
{
	char	*result;

	if (!cmd_row || !seek)
		return (NULL);
	printf("cmd: %sseek: %s", cmd_row, seek); //borrar
	if (ft_strcspn(cmd_row, seek) == ft_strlen(cmd_row))
		return (ft_strdup(cmd_row));
	else
	{
		result = ft_calloc(ft_strcspn(cmd_row, seek) + 1, sizeof(char));
		if (!result)
			return (NULL);
		copy_segments(result, cmd_row, ft_strcspn(cmd_row, seek));
	}
	return (result);
}

void	ms_loop_minishell_nointeractive(t_mshell *data)
{
	char	*read_line;
	char	*cmd_row;

	data->input_row = NULL;
	while (1)
	{
		cmd_row = get_next_line2(STDIN_FILENO);
		read_line = ms_clean_cmd(cmd_row, "\n");
		printf("read_line apunta a: %p\n", (void *)read_line);
		ft_free_ptr((void **)&cmd_row);
		if (!read_line)
		{
			ft_free_ptr((void **)&read_line);
			break ;
		}
		if (read_line[0] == '\0')
		{
			ft_free_ptr((void **)&read_line);
			continue ;
		}
		if (!ms_parcetoken_mini(data, read_line))
		{
			free(read_line);
			continue ;
		}
		ms_exec(data);
		ft_free_ptr((void **)&read_line);
		printf("liberando read_line final2: %p\n", (void *)read_line);
	}
	ft_free_ptr((void **)&cmd_row);
	ft_free_ptr((void **)&read_line);
	printf("liberando read_line final: %p\n", (void *)read_line);
	ft_lstclear(&data->env, free);
	ft_free_ptr((void **)&data->prompt);
	ft_free_ptr((void **)&data->input_row);
}

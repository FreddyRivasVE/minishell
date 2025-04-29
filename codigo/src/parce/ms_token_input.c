/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_token_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 14:23:12 by frivas            #+#    #+#             */
/*   Updated: 2025/04/29 15:05:56 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ms_set_redir_type(char *word)
{
	if (word[0] == '<' && word[1] == '<')
		return ("HEREDOC");
	else if (word[0] == '>' && word[1] == '>')
		return ("OUTPUTAPPEND");
	else if (word[0] == '<')
		return ("INPUT");
	else
		return ("OUTPUT");
}

int	ms_array_count(char ***array)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while (array [i])
	{
		j = 0;
		while (array[i][j])
		{
			count++;
			j++;
		}
		i++;
	}
	return (count);
}

static char	*ms_get_token(char	*word)
{
	if (!ft_strcmp(word, "<") || !ft_strcmp(word, "<<")
		|| !ft_strcmp(word, ">") || !ft_strcmp(word, ">>"))
		return (ms_set_redir_type(word));
	else
		return ("COMMAND");
}

static char	*ms_subfix_redir(char *tag)
{
	if (!ft_strcmp(tag, "HEREDOC")
		|| !ft_strcmp(tag, "OUTPUTAPPEND")
		|| !ft_strcmp(tag, "INPUT")
		|| !ft_strcmp(tag, "OUTPUT" ))
		return ("REDIR");
	return ("COMMAND");
}

void	ms_token_input(t_mshell *data)
{
	int		i;
	int		j;
	char	***inpt;
	int		k;

	inpt = data->inputs->splitaftpipes;
	data->inputs->tag = ft_calloc(ms_array_count(inpt) + 1, sizeof(char *));
	if (!data->inputs->tag)
		return ;
	i = 0;
	k = 0;
	while (inpt[i])
	{
		j = 0;
		while (inpt[i][j])
		{
			data->inputs->tag[k] = ms_get_token(inpt[i][j]);
			if (j > 0 && !ft_strcmp(data->inputs->tag[k], "COMMAND"))
				data->inputs->tag[k] = ms_subfix_redir(data->inputs->tag[k - 1]);
			j++;
			k++;
		}
		i++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_control_expand_heredoc.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 15:29:32 by frivas            #+#    #+#             */
/*   Updated: 2025/05/17 18:25:28 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ms_control_expand_heredoc(t_mshell *data)
{
	int		i;
	bool	sq;
	bool	dq;
	int		start;
	int		end;
	char	*temp;

	i = 0;
	temp = ft_calloc(1, sizeof(char));
	sq = false;
	dq = false;
	while (data->input_row[i])
	{
		start = i;
		while (data->input_row[i] && data->input_row[i] != '<')
		{
			sq = toggle_simples(data->input_row[i], sq, dq);
			dq = toggle_doubles(data->input_row[i], sq, dq);
			i++;
		}
		end = i;
		temp = ft_strjoin_free(temp, ft_substr(data->input_row, start, end - start));
		printf ("SALE1: start: %d end: %d %s\n", start, end, temp); //borrar
		start = i;
		if (data->input_row[i] != '\0' && data->input_row[i + 1] && data->input_row[i + 1] == '<' && !(sq || dq))
		{
			i = i + 2;
			end = i;
			temp = ft_strjoin_free(temp, ft_substr(data->input_row, start, end - start));
			printf ("SALE2: start: %d end: %d %s\n", start, end, temp); //borrar
			start = i;
			while (data->input_row[i] && data->input_row[i] != '\'' && data->input_row[i] != '\"' && data->input_row[i] != '$')
				i++;
			end = i;
			temp = ft_strjoin_free(temp, ft_substr(data->input_row, start, end - start));
			printf ("SALE3: %s\n", temp); //borrar
			if (data->input_row[i] == '$')
			{
				temp = ft_strjoin_free(temp, ft_strdup("\'"));
				start = i;
				while (data->input_row[i] && !ft_isspace(data->input_row[i]))
					i++;
				end = i;
				temp = ft_strjoin_free(temp, ft_substr(data->input_row, start, end - start));
				temp = ft_strjoin_free(temp, ft_strdup("'"));
				printf ("SALE5: %s\n", temp); //borrar
			}
			else if (data->input_row[i] == '\"')
			{
				temp = ft_strjoin_free(temp, ft_strdup("'"));
				i++;
				start = i;
				while (data->input_row[i] && data->input_row[i] != '\"')
				i++;
				end = i;
				temp = ft_strjoin_free(temp, ft_substr(data->input_row, start, end - start));
				temp = ft_strjoin_free(temp, "'");
				i++;
			}
			else
			{
				start = i;
				while (data->input_row[i] && data->input_row[i] !='\'')
					i++;
				end = i;
				temp = ft_strjoin_free(temp, ft_substr(data->input_row, start, end - start));
			}
		}
		else if (data->input_row[i])
		{
			end = i + 1;
			printf ("SALE6: start: %d end: %d %s\n", start, end, temp); //borrar
			temp = ft_strjoin_free(temp, ft_substr(data->input_row, start, end - start));
			printf ("SALE7: start: %d end: %d %s\n", start, end, temp); //borrar
			i++;
		}
		
	}
	free(data->input_row);
	data->input_row = temp;
	printf ("SALE: %s\n", data->input_row); //borrar
	return (true);
}

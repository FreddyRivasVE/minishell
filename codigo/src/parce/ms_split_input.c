/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_split_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 21:46:39 by frivas            #+#    #+#             */
/*   Updated: 2025/04/04 01:09:27 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool    ms_check_char(char c, char *quotation)
{
    if (c == '\'' || c == '"')
    {
        if (*quotation == '\0')
            *quotation = c;
        else if (*quotation == c)
            *quotation = '\0';
        return (true);
    }
    return (false);
}

void    append_char(char *pre_cmmd, char c, int *index)
{
    pre_cmmd[*index] = c;
    (*index)++;
}

char    *extract_single_command(const char **start)
{
    char *pre_cmmd;
    int index;
    char quotation;

    pre_cmmd = (char *)ft_calloc(1024, sizeof(char));
    if (!pre_cmmd)
        return (NULL);
    index = 0;
    quotation = '\0';
    while (**start)
    {
        if (ft_isspace(**start) && quotation == '\0' && index > 0)
            break;
        if (**start == '|' && quotation == '\0')
            break;
        if (!ms_check_char(**start, &quotation))
            append_char(pre_cmmd, **start, &index);
        (*start)++;
    }
    if (index > 0)
        pre_cmmd[index] = '\0';
    return (pre_cmmd);
}

void skip_separators(const char **start)
{
    while (**start)
    {
        if (!ft_isspace(**start) && **start != '|')
            break;
        (*start)++;
    }
}

char **extract_commands(const char *start)
{
    char **commands;
    int cmd_count;

    commands = (char **)malloc(100 * sizeof(char *));
    if (!commands)
        return (NULL);
    cmd_count = 0;
    while (*start)
    {
        commands[cmd_count] = extract_single_command(&start);
        if (commands[cmd_count])
            cmd_count++;
        skip_separators(&start);
    }
    commands[cmd_count] = NULL;
    return (commands);
}

char **ms_split_input(char *str)
{
    if (!str)
        return (NULL);
    return (extract_commands(str));
}


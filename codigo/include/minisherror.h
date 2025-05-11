/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minisherror.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:40:59 by frivas            #+#    #+#             */
/*   Updated: 2025/05/11 12:15:19 by brivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHERROR_H
# define MINISHERROR_H

# define MINI   "minishell: "
# define SYNTAX "minishell: syntax error"
# define SYNTAXPIPE "minishell: syntax error near unexpected token `|'"
# define SYNTAXREDIR "minishell: syntax error near unexpected token `newline'"
# define MALLOC "minishell: malloc"
# define INITDIRWRONG "minishell-init: error retrieving current directory"
# define ERRORCREATENODO  	    "Error creating node"
# define SUBJECTOPTIONERROR 	"unset: subject doesn't allow option"
# define SUBJECTECHOOPTERROR 	"echo: subject only allow -n option"
# define SUBJECTEXPORTERROR 	"export: subject doesn't options"
# define SPECIALCHAR 			": not an identifier"
# define ERRORHEREDOC			"minishell warning: here-doc delimited by EOF"
# define NOFILEDIRCTORY         ": No such file or directory"
# define ERROCOMMAND            ": command not found"
# define ENOMEM 12

#endif
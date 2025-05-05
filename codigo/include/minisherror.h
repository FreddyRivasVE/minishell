/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minisherror.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:40:59 by frivas            #+#    #+#             */
/*   Updated: 2025/05/05 15:42:43 by frivas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHERROR_H
# define MINISHERROR_H

# define SYNTAX "minishell: syntax error"
# define SYNTAXPIPE "minishell: syntax error near unexpected token `|'"
# define SYNTAXREDIR "minishell: syntax error near unexpected token `newline'"
# define MALLOC "minishell: malloc"
# define INITDIRWRONG "minishell-init: error retrieving current directory"

/*Este error indica: no hay suficiente memoria disponible.*/
# define ENOMEM 12
# define ERRORCREATENODO  		"Error creating node"
# define SUBJECTOPTIONERROR 	"unset: subject doesn't allow option"
# define SUBJECTECHOOPTERROR 	"echo: subject only allow -n option"
# define SUBJECTEXPORTERROR 	"export: subject doesn't options"
# define SPECIALCHAR 			": not an identifier"
# define ERRORHEREDOC			"minishell warning: here-doc delimited by EOF"

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minisherror.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera@student.42madrid.com <brivera>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:40:59 by frivas            #+#    #+#             */
/*   Updated: 2025/04/21 20:06:49 by brivera@stu      ###   ########.fr       */
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

#endif
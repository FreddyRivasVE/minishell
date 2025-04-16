/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minisherror.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frivas <frivas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 15:40:59 by frivas            #+#    #+#             */
/*   Updated: 2025/04/16 18:24:49 by frivas           ###   ########.fr       */
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
# define ERRORCREATENODO  "Error al crear nodo\n"
# define SUBJECTOPTIONERROR "unset: subject doesn't allow opts."
# define SUBJECTECHOOPTERROR "echo: subject only allow -n option"

#endif
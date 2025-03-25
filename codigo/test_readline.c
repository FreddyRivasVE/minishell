/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_readline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera <brivera@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 23:26:58 by frivas            #+#    #+#             */
/*   Updated: 2025/03/19 10:54:48 by brivera          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char *input;

	while (1)
	{
		input = readline("minishell$ ");  // Mostrar el prompt y leer la entrada
		if (!input) // Detectar Ctrl+D (EOF)
		{
			printf("exit\n");
			break;
		}
		if (*input) // Si la entrada no está vacía, agregarla al historial
			add_history(input);
		printf("Entrada: %s\n", input);  // Mostrar lo que el usuario escribió
		free(input);  // Liberar memoria asignada por readline
	}
	return 0;
}

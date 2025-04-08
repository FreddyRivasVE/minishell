/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_00.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera@student.42madrid.com <brivera>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 19:41:48 by brivera@stu       #+#    #+#             */
/*   Updated: 2025/04/05 19:52:20 by brivera@stu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	split_list(t_list *head, t_list **left, t_list **right)
{
	t_list	*slow;
	t_list	*fast;

	slow = head;
	fast = head->next;
	while (fast && fast->next)
	{
		slow = slow->next;
		fast = fast->next->next;
	}
	*left = head;
	*right = slow->next;
	slow->next = NULL;
}

t_list	*merge_sorted_lists(t_list *a, t_list *b)
{
	if (!a)
		return (b);
	if (!b)
		return (a);
	if (ft_strcmp((char *)a->content, (char *)b->content) <= 0)
	{
		a->next = merge_sorted_lists(a->next, b);
		return (a);
	}
	else
	{
		b->next = merge_sorted_lists(a, b->next);
		return (b);
	}
}

void	ms_merge_sort(t_list **head)
{
	t_list	*left;
	t_list	*right;

	if (!*head || !(*head)->next)
		return ;
	left = NULL;
	right = NULL;
	split_list(*head, &left, &right);
	ms_merge_sort(&left);
	ms_merge_sort(&right);
	*head = merge_sorted_lists(left, right);
}
//pasos
// 1. copiar la lista
// 2. Ordenar la lista con Merge Sort
// 3. imprimir 
// 4. limpiar y salir

int	ms_export_print_list(t_list **env)
{
	t_list	*copy_env;

	copy_env = ms_copy_export_env(env);
	if (!copy_env)
		return (ENOMEM);
	ms_merge_sort(&copy_env);
	print_list_sorted(&copy_env);
	ft_lstclear(&copy_env, free);
	return (0);
}

//export sin opciones pero con argumentos
int	ms_export(char **command, t_mshell *data)
{
	t_list	*new_node;
	char	*argument;
	int		exit;

	exit = 0;
	if (command[1])
	{
		if (command[1][0] == '-')
			return (ft_putendl_fd("export: subject doesn't options", 2), 2);
		if (ft_isdigit(command[1][0]))
			return (ft_putendl_fd("export: not an identifier", 2), 2);
		argument = ft_strdup(command[1]);
		if (!argument)
			return (perror("malloc"), 1);
		new_node = ft_lstnew(argument);
		if (!new_node)
			return (perror("malloc"), ms_free_ptr((void *)argument), 1);
		ft_lstadd_back(&data->env, new_node);
	}
	else
		exit = ms_export_print_list(&data->env);
	return (exit);
}

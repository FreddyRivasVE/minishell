/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera@student.42madrid.com <brivera>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 19:49:34 by brivera@stu       #+#    #+#             */
/*   Updated: 2025/04/04 21:40:28 by brivera@stu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_list_content_char(t_list **lst)
{
	t_list	*current;

	current = *lst;
	while (current != NULL)
	{
		if (current->content != NULL)
			printf("%s\n", (char *)current->content);
		current = current->next;
	}
}

/*
Compara dos strings
0  si `s1` y `s2` son iguales.
<0 si `s1` es menor que `s2` (en orden ASCII).
>0 si `s1` es mayor que `s2`. 
Nota:`unsigned char` para manejar valores >127 correctamente.
 */

 int	ft_strcmp(const char *s1, const char *s2)
 {
	 int	i;
 
	 i = 0;
	 while (s1[i] && s2[i] && s1[i] == s2[i])
		 i++;
	 return ((unsigned char)s1[i] - (unsigned char)s2[i]);
 }

t_list	*ms_copy_export(t_list **env)
{
	char	*envread;
	t_list	*new_node;
	t_list	*env_list;
	t_list	*current;

	env_list = NULL;
	current = *env;
	while (current != NULL)
	{
		envread = ft_strdup(current->content);
		if (!envread)
		{
			perror("malloc");
			ft_lstclear(&env_list, free);
			break ;
		}
		new_node = ft_lstnew(envread);
		if (!new_node)
		{
			perror("molloc nodo");
			free(envread);
			ft_lstclear(&env_list, free);
			break ;
		}
		ft_lstadd_back(&env_list, new_node);
		current = current->next;
	}
	return (env_list);
}

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


void	ms_export_print_list(t_list **env)
{
	t_list	*copy_env;

	copy_env = ms_copy_export(env);
	ms_merge_sort(&copy_env);
	print_list_content_char(copy_env);
	ft_lstclear(&copy_env, free);
}

//export sin opciones pero con argumentos
int	ms_export(char **command, t_mshell *data)
{
	t_list	*new_node;
	char	*content;

	if (command[1])
	{
		if (command[1][0] == '-')
			return (ft_putendl_fd("export: subject doesn't options", 2), 2);
		if (ft_isdigit(command[1][0]))
			return (ft_putendl_fd("export: not an identifier", 2), 2);
		content = ft_strdup(command[1]);
		if (!content)
			return (perror("malloc"), 1);
		new_node = ft_lstnew(content);
		if (!new_node)
		{
			perror("malloc");
			free(content);
			return (1);
		}
		ft_lstadd_back(&env_list, new_node);
	}
	else
		ms_export_print_list(data->env);
}

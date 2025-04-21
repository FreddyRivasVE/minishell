/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_02.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brivera@student.42madrid.com <brivera>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 18:48:12 by brivera@stu       #+#    #+#             */
/*   Updated: 2025/04/21 18:56:59 by brivera@stu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_list_sorted(t_list **lst)
{
	t_list	*current;

	current = *lst;
	while (current != NULL)
	{
		if (current->content != NULL)
			printf("declare -x %s\n", (char *)current->content);
		current = current->next;
	}
}

static void	split_list(t_list *head, t_list **left, t_list **right)
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

static t_list	*merge_sorted_lists(t_list *a, t_list *b)
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

static void	ms_merge_sort(t_list **head)
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

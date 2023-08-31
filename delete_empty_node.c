/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_empty_node.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyassine <eyassine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 16:58:20 by eyassine          #+#    #+#             */
/*   Updated: 2023/08/31 18:10:48 by eyassine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

void	fill_operator_content(char *content, char *s, int *i)
{
	content[0] = *s;
	if (content[0] == s[1] && s[1] != '|')
	{
		content[1] = s[1];
		content[2] = '\0';
		*i += 1;
	}
	else
		content[1] = '\0';
}

t_list	*delete_empty_node(t_list *list, t_list *head)
{
	t_list	*tmp;

	if (list->prev)
	{
		list->prev->next = list->next;
		if (list->next)
			list->next->prev = list->prev;
		tmp = list;
		list = list->next;
	}
	else
	{
		if (list->next)
			list->next->prev = NULL;
		tmp = list;
		list = list->next;
		head = list;
	}
	free(tmp->content);
	free(tmp);
	return (head);
}

t_list	*check_empty_node(t_list *list)
{
	t_list	*head;

	head = list;
	while (list)
	{
		if (!list->content[0])
		{
			head = delete_empty_node(list, head);
			list = head;
		}
		else
			list = list->next;
	}
	return (head);
}

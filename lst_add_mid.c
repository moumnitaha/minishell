/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_add_mid.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyassine <eyassine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 16:56:53 by eyassine          #+#    #+#             */
/*   Updated: 2023/08/17 10:54:54 by eyassine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

t_list	*lst_add_mid(t_list *list, t_list *head)
{
	t_list	*tmp;
	t_list	*new;

	new = list->prev;
	tmp = list->next;
	head->prev = list->prev;
	list->prev->next = head;
	while (head)
	{
		if (!head->next)
		{
			head->next = tmp;
			if (list->next)
				list->next->prev = head;
			free(list->content);
			free(list);
			break ;
		}
		head = head->next;
	}
	return (new);
}

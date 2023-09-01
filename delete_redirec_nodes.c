/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_redirec_nodes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoumni <tmoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 10:48:53 by eyassine          #+#    #+#             */
/*   Updated: 2023/08/17 18:55:42 by tmoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

t_list	*delete_redirec_nodes(t_list *list)
{
	t_list	*head;

	head = list;
	while (list)
	{
		if (list->tokens > EMPTY && list->tokens <= OUT_REDIREC
			&& list->tokens != PIPE)
		{
			list->tokens = 0;
			list->next->tokens = 0;
		}
		list = list->next;
	}
	return (head);
}

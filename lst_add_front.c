/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_add_front.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyassine <eyassine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 16:56:17 by eyassine          #+#    #+#             */
/*   Updated: 2023/08/24 18:27:40 by eyassine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

void	lst_add_front(t_list *list, t_list *new)
{
	while (new)
	{
		if (!new->next)
		{
			new->next = list->next;
			if (list->next)
				list->next->prev = new;
			free(list->content);
			free(list);
			break ;
		}
		new = new->next;
	}
}

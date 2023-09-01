/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_add_back.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoumni <tmoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 18:44:15 by eyassine          #+#    #+#             */
/*   Updated: 2023/08/31 20:05:54 by tmoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

void	lst_add_back(t_list *head, t_list *new)
{
	if (!new)
	{
		ft_free_list(head);
		exit(1);
	}
	while (head)
	{
		if (!head->next)
		{
			new->prev = head;
			head->next = new;
			break ;
		}
		head = head->next;
	}
}

void	ft_free_sub(char *sub, char *sub2, char *env)
{
	free(sub2);
	free(sub);
	free(env);
}

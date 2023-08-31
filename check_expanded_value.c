/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_expanded_value.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyassine <eyassine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 10:38:34 by eyassine          #+#    #+#             */
/*   Updated: 2023/08/31 18:15:47 by eyassine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

int	check_space(char *cont)
{
	int	s_q;
	int	d_q;

	s_q = 0;
	d_q = 0;
	while (*cont)
	{
		check_for_quotes(*cont, &s_q, &d_q);
		if (ft_iswhitespace(*cont) && !s_q && !d_q)
			return (1);
		cont++;
	}
	return (0);
}

void	ft_identify_expand(t_list *list)
{
	while (list)
	{
		list->expand = 1;
		list = list->next;
	}
}

t_list	*ft_operate(t_list *list)
{
	t_list	*new;
	t_list	*head;

	head = list;
	new = list;
	while (list)
	{
		if (check_space(list->content))
		{
			new = lexer(list->content);
			if (!new)
				check_head_fail(NULL, list);
			ft_identify_expand(new);
			if (!list->prev)
			{
				lst_add_front(list, new);
				list = new;
				head = new;
			}
			else
				list = lst_add_mid(list, new);
		}
		list = list->next;
	}
	return (head);
}

t_list	*check_expanded_value(t_list *list)
{
	t_list	*head;

	head = ft_operate(list);
	tokenize_list(head);
	return (head);
}

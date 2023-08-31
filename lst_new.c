/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_new.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyassine <eyassine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 18:38:52 by eyassine          #+#    #+#             */
/*   Updated: 2023/08/28 16:11:32 by eyassine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

t_list	*lst_new(void)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->next = NULL;
	new->prev = NULL;
	new->content = NULL;
	new->tokens = 0;
	new->expand = 0;
	new->any_quotes = 0;
	new->outside_quote = 0;
	return (new);
}

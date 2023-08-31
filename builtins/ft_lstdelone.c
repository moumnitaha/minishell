/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoumni <tmoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 17:41:49 by tmoumni           #+#    #+#             */
/*   Updated: 2023/08/16 15:35:35 by tmoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

void	ft_lst_delete_node(t_env **head_ref, char *name_to_delete)
{
	t_env	*current;
	t_env	*prev;

	current = *head_ref;
	prev = NULL;
	while (current != NULL)
	{
		if (ft_strmatch(current->name, name_to_delete))
		{
			if (prev != NULL)
				prev->next = current->next;
			else
				*head_ref = current->next;
			free(current->name);
			free(current->value);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

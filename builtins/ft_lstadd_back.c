/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoumni <tmoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 16:00:52 by tmoumni           #+#    #+#             */
/*   Updated: 2023/08/16 14:24:37 by tmoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

void	ft_lstadd_back(t_env **lst, t_env *new)
{
	t_env	*back;

	back = *lst;
	if (*lst == NULL)
		*lst = new;
	else
	{
		while (back->next != NULL)
			back = back->next;
		back->next = new;
	}
}

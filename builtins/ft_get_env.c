/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoumni <tmoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 12:40:15 by tmoumni           #+#    #+#             */
/*   Updated: 2023/08/02 17:07:59 by tmoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

char	*ft_get_env(char *str)
{
	t_env	*head;

	head = g_msh.env;
	while (head)
	{
		if (ft_strmatch(head->name, str))
			return (head->value);
		head = head->next;
	}
	return (NULL);
}

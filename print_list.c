/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoumni <tmoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 18:44:15 by eyassine          #+#    #+#             */
/*   Updated: 2023/08/17 18:52:44 by tmoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

void	print_list(t_list *list)
{
	while (list)
	{
		printf("|%s|  ", list->content);
		printf("tokens %d\n", list->tokens);
		list = list->next;
	}
}

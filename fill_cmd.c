/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyassine <eyassine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 20:17:06 by eyassine          #+#    #+#             */
/*   Updated: 2023/08/16 18:45:23 by eyassine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

int	lst_size(t_list *list, t_tokens del)
{
	int	counter;

	counter = 0;
	while (list && list->tokens != del)
	{
		if (list->tokens != 0)
			counter++;
		list = list->next;
	}
	return (counter);
}

void	allocate_cmd(t_cmd *cmd_l, t_list *list)
{
	int	words;

	words = lst_size(list, PIPE);
	if (!words)
		return ;
	cmd_l->cmd = malloc(sizeof(char *) * (words + 1));
	if (!cmd_l->cmd)
		return ;
	cmd_l->cmd[words] = NULL;
}

t_cmd	*fill_cmd(t_list *list, t_cmd *cmd_l)
{
	t_cmd	*head;
	int		words;
	int		i;

	head = cmd_l;
	allocate_cmd(cmd_l, list);
	i = 0;
	while (list)
	{
		if (list->tokens != PIPE && list->tokens != 0)
			cmd_l->cmd[i++] = ft_strcp(list->content);
		else if (list->tokens == PIPE)
		{
			cmd_l = cmd_l->next;
			words = lst_size(list->next, PIPE);
			cmd_l->cmd = malloc(sizeof(char *) * (words + 1));
			cmd_l->cmd[words] = NULL;
			i = 0;
		}
		list = list->next;
	}
	return (head);
}

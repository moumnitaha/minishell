/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyassine <eyassine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 15:30:41 by eyassine          #+#    #+#             */
/*   Updated: 2023/08/28 16:23:55 by eyassine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

t_cmd	*newnode(void)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->cmd = NULL;
	new->redirec = NULL;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	first_redirect(t_cmd *head)
{
	if (head && head->redirec)
	{
		while (head->redirec->prev)
			head->redirec = head->redirec->prev;
	}
}

t_cmd	*cmd_redirect_list(t_list *list, t_cmd *head)
{
	t_list	*tmp;

	tmp = NULL;
	if (list->tokens == HEREDOC || list->tokens == IN_REDIREC
		|| list->tokens == APP || list->tokens == OUT_REDIREC)
	{
		tmp = head->redirec;
		head->redirec = lst_new();
		head->redirec->content = ft_strcp(list->next->content);
		head->redirec->tokens = list->tokens;
		head->redirec->any_quotes = list->next->any_quotes;
		if (tmp)
		{
			head->redirec->prev = tmp;
			head->redirec->prev->next = head->redirec;
		}
	}
	return (head);
}

t_cmd	*create_cmd_nodes(t_list *list, t_cmd *head)
{
	if (list->tokens == PIPE)
	{
		first_redirect(head);
		head->next = newnode();
		head->next->prev = head;
		head = head->next;
	}
	return (head);
}

t_cmd	*build_command(t_list *list)
{
	t_cmd	*head;
	t_cmd	*first;
	t_list	*begin;

	head = NULL;
	first = NULL;
	begin = list;
	while (list)
	{
		head = create_cmd_nodes(list, head);
		if (!head)
		{
			head = newnode();
			check_head_fail(head, begin);
			first = head;
		}
		cmd_redirect_list(list, head);
		list = list->next;
	}
	first_redirect(head);
	list = delete_redirec_nodes(begin);
	if (list && !fill_cmd(list, first))
		cmd_fails(list, first);
	return (first);
}

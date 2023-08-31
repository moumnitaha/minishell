/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoumni <tmoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 19:59:02 by eyassine          #+#    #+#             */
/*   Updated: 2023/08/25 16:20:03 by tmoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

void	link_it(t_list *head, t_list *new)
{
	if (head)
	{
		head->next = new;
		new->prev = head;
	}
}

void	check_operator_fail(t_list *new, int oper, t_list *l_hd, t_list *hd)
{
	if (!new && oper)
	{
		ft_free_list(l_hd);
		ft_free_list(hd);
		exit(1);
	}
}

int	check_pipe(t_list *list)
{
	if (!list->prev)
	{
		write(2, "minishell: syntax error near unexpected token `|'\n", 51);
		g_msh.exit_status = 258;
		return (0);
	}
	else if (!list->next)
	{
		write(2, "minishell: syntax error near unexpected token `|'\n", 51);
		g_msh.exit_status = 258;
		return (0);
	}
	else if (list->next)
	{
		if (list->next->tokens == PIPE)
		{
			write(2, "minishell: syntax error near unexpected token `|'\n", 51);
			g_msh.exit_status = 258;
			return (0);
		}
	}
	return (1);
}

int	check_if_file(t_list *list)
{
	if (list->next)
	{
		if (list->next->tokens != WORD && list->next->tokens != OPTION
			&& list->next->tokens != DOUBLE_QUOTE
			&& list->next->tokens != SINGLE_QUOTE)
		{
			write(2, "minishell: syntax error near unexpected token \n", 48);
			g_msh.exit_status = 258;
			return (0);
		}
		if (list->next->tokens == OPTION)
			list->next->tokens = WORD;
	}
	else if (!list->next)
	{
		write(2, "minishell: syntax error near unexpected token \n", 48);
		g_msh.exit_status = 258;
		return (0);
	}
	return (1);
}

int	check_syntax(t_list *list)
{
	while (list)
	{
		if (list->tokens == PIPE)
		{
			if (!check_pipe(list))
				return (0);
		}
		else if (list->tokens == OUT_REDIREC || list->tokens == IN_REDIREC 
			|| list->tokens == HEREDOC || list->tokens == APP)
		{
			if (!check_if_file(list))
				return (0);
		}
		list = list->next;
	}
	return (1);
}

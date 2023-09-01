/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoumni <tmoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 21:38:28 by eyassine          #+#    #+#             */
/*   Updated: 2023/08/29 10:38:24 by tmoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

void	check_outside_quote(t_list *list)
{
	if ((list->outside_quote && list->tokens == DOUBLE_QUOTE)
		|| (list->outside_quote && list->tokens == SINGLE_QUOTE))
		list->tokens = WORD;
}

void	check_head_fail(t_cmd *cmd, t_list *list)
{
	if (!cmd)
	{
		ft_free_list(list);
		exit(1);
	}
}

t_list	*ft_lexer(int count_word, char *read, t_list *head)
{
	t_list	*new;
	int		i;

	i = 0;
	while (i < count_word)
	{
		if (!head)
		{
			head = lst_new();
			if (!head)
				return (NULL);
			read = ft_fill_content(head, read);
		}
		else
		{
			new = lst_new();
			lst_add_back(head, new);
			read = ft_fill_content(new, read);
		}
		i++;
	}
	return (head);
}

t_list	*lexer(char *read)
{
	int		count_word;
	t_list	*head;

	head = NULL;
	count_word = howmany_words(read);
	head = ft_lexer(count_word, read, head);
	return (head);
}

void	exit_with(int e)
{
	write(1, "exit\n", 5);
	exit(e);
}

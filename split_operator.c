/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_operator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyassine <eyassine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 18:14:21 by eyassine          #+#    #+#             */
/*   Updated: 2023/08/28 16:19:34 by eyassine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

void	check_content_fails(t_list *list, t_list *list_head, t_list *new)
{
	if (!list->content)
	{
		ft_free_list(list_head);
		ft_free_list(list);
		if (new)
			ft_free_list(new);
		exit(1);
	}
}

int	check_operation(char *s, int i)
{
	int	j;

	if (!s ||!s[0])
		return (0);
	j = i;
	i = 0;
	while (i < j)
	{
		if (s[i] == '|' || (s[i] == '<') || (s[i] == '>'))
			return (1);
		i++;
	}
	return (0);
}

void	check_for_quotes(char c, int *s_quotes, int *d_quotes)
{
	if (c == 34 || c == 39)
	{
		if (c == 34 && !*s_quotes)
		{
			if (*d_quotes)
				*d_quotes = 0;
			else
				*d_quotes = 1;
		}
		else if (c == 39 && !*d_quotes)
		{
			if (*s_quotes)
				*s_quotes = 0;
			else
				*s_quotes = 1;
		}
	}
}

int	chars_to_split(char *s)
{
	int	i;
	int	s_quotes;
	int	d_quotes;

	i = 0;
	d_quotes = 0;
	s_quotes = 0;
	while (*s)
	{
		check_for_quotes(*s, &s_quotes, &d_quotes);
		if (!s_quotes && !d_quotes)
		{
			if (*s == '|' || *s == '>' || *s == '<')
				break ;
		}
		i++;
		s++;
	}
	return (i);
}

t_list	*split_operator(t_list *list)
{
	t_list	*new;
	t_list	*head;

	new = NULL;
	head = list;
	while (list)
	{
		new = fill_new_nodes(list);
		if (new)
		{
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
	head = check_empty_node(head);
	tokenize_list(head);
	return (head);
}

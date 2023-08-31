/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_new_node.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyassine <eyassine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 16:52:48 by eyassine          #+#    #+#             */
/*   Updated: 2023/08/31 18:08:49 by eyassine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

t_list	*link_list(t_list *new, t_list *head, t_list *first_node, int first)
{
	if (!first)
	{
		first_node = head;
		first = 1;
	}
	if (new)
	{
		new->next = head;
		head->prev = new;
	}
	return (first_node);
}

t_list	*fill_operator_node(t_list *head, int *operation, int *i, char *s)
{
	t_list	*new;

	new = NULL;
	if (*operation)
	{
		new = lst_new();
		if (!new)
			return (NULL);
		link_it(head, new);
		new->content = malloc(sizeof(char) * 3);
		if (!new->content)
		{
			free(new);
			return (NULL);
		}
		fill_operator_content(new->content, s, i);
		*operation = 0;
	}
	return (new);
}

void	ft_fill_word_node(char *s, t_list *head, int *operation, int *index)
{
	int	s_quotes;
	int	d_quotes;
	int	i;

	s_quotes = 0;
	d_quotes = 0;
	i = 0;
	while (*s && head->content)
	{
		check_for_quotes(*s, &s_quotes, &d_quotes);
		if (!s_quotes && !d_quotes)
		{
			if (*s == '|' || *s == '>' || *s == '<')
			{
				*operation = 1;
				head->content[i] = '\0';
				break ;
			}
		}
		head->content[i++] = *s;
		s++;
		*index += 1;
	}
	head->content[i] = '\0';
}

t_list	*ft_fill_(char *s, t_list *headd)
{
	int		i;
	int		operation;
	t_list	*head;
	t_list	*new;

	operation = 0;
	i = 0;
	new = NULL;
	while (*(s + i))
	{
		head = lst_new();
		if (!head)
			check_head_fail(NULL, headd);
		head->content = malloc(sizeof(char) * ((chars_to_split((s + i)) + 1)));
		check_content_fails(head, headd, headd);
		headd = link_list(new, head, headd, i);
		ft_fill_word_node((s + i), head, &operation, &i);
		new = fill_operator_node(head, &operation, &i, s + i);
		check_operator_fail(new, operation, headd, headd);
		if (*(s + i))
			i++;
	}
	return (headd);
}

t_list	*fill_new_nodes(t_list *list)
{
	int		chars;
	t_list	*new;

	new = NULL;
	if (list->tokens == WORD || list->tokens == OPTION)
	{
		chars = check_operation(list->content, ft_strlen(list->content));
		if (chars)
			new = ft_fill_(list->content, new);
	}
	return (new);
}

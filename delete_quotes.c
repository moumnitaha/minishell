/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyassine <eyassine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 13:34:00 by eyassine          #+#    #+#             */
/*   Updated: 2023/08/24 18:38:01 by eyassine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

int	has_quotes(char *s)
{
	while (*s)
	{
		if (*s == 39 || *s == 34)
			return (1);
		s++;
	}
	return (0);
}

char	*inside_q(char *s, char *new, int *i, int quote)
{
	s++;
	while (*s && *s != quote)
	{
		new[*i] = *s;
		*i += 1;
		s++;
	}
	return (s);
}

char	*ft_delete_quotes(char *s)
{
	int		len;
	char	*new;
	int		i;

	len = len_without_quotes(s);
	new = malloc(sizeof(char) * (ft_strlen(s) - len) + 1);
	if (!new)
		return (NULL);
	i = 0;
	while (*s)
	{
		if (*s == 39 || *s == 34)
		{
			if (*s == 39)
				s = inside_q(s, new, &i, 39);
			else
				s = inside_q(s, new, &i, 34);
		}
		else
			new[i++] = *s;
		s++;
	}
	new[i] = '\0';
	return (new);
}

t_list	*delete_quotes(t_list *head)
{
	t_list	*new;
	char	*prev;

	new = head;
	while (new)
	{
		if (has_quotes(new->content))
		{
			new->any_quotes = 1;
			prev = new->content;
			new->content = ft_delete_quotes(new->content);
			if (!new->content)
				new->content = prev;
			else
				free(prev);
		}
		new = new->next;
	}
	return (new);
}

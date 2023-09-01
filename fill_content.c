/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_content.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyassine <eyassine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 16:26:34 by eyassine          #+#    #+#             */
/*   Updated: 2023/08/28 16:31:40 by eyassine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

int	count_chars(char *read)
{
	int	count;

	count = 0;
	while (ft_iswhitespace(*read))
		read++;
	while (*read)
	{
		if (*read == 34 || *read == 39)
		{
			if (*read == 34)
				read = chars_inside_quotes(&count, read, 34);
			else
				read = chars_inside_quotes(&count, read, 39);
		}
		if (ft_iswhitespace(*read))
			return (count);
		read++;
		count++;
	}
	return (count);
}

char	*allocate_node_content(char *read, t_list *list)
{
	char	*content;
	int		count;

	count = count_chars(read);
	content = malloc(sizeof(char) * (count + 1));
	if (!content)
	{
		ft_free_list(list);
		free(read);
		exit(1);
	}
	content[count] = '\0';
	return (content);
}

char	*fill_inside_quotes(char *read, t_list *list, int *i)
{
	int	quote;

	quote = *read;
	if (quote == 34)
		list->tokens = DOUBLE_QUOTE;
	else
		list->tokens = SINGLE_QUOTE;
	while (*read)
	{
		list->content[*i] = *read;
		*i += 1;
		read++;
		if (*read == quote)
			break ;
	}
	list->content[*i] = *read;
	*i += 1;
	return (read);
}

char	*fill_outside_quotes(t_list *list, char *read, int *i)
{
	while (*read && *read != 39 && *read != 34)
	{
		if (ft_iswhitespace(*read))
			break ;
		list->outside_quote = 1;
		list->content[*i] = *read;
		*i += 1;
		read++;
	}
	return (read);
}

char	*ft_fill_content(t_list *list, char *read)
{
	int	i;

	i = 0;
	list->content = allocate_node_content(read, list);
	while (*read && ft_iswhitespace(*read))
		read++;
	while (*read && !ft_iswhitespace(*read))
	{
		if (*read == 34 || *read == 39)
		{
			read = fill_inside_quotes(read, list, &i);
			read++;
		}
		if (ft_iswhitespace(*read))
			break ;
		read = fill_outside_quotes(list, read, &i);
	}
	list->content[i] = '\0';
	check_outside_quote(list);
	return (read);
}

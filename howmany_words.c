/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   howmany_words.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyassine <eyassine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 16:23:24 by eyassine          #+#    #+#             */
/*   Updated: 2023/08/31 18:15:34 by eyassine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

int	skip_space(char *s)
{
	int	i;

	i = 0;
	while (ft_iswhitespace(s[i]))
		i++;
	return (i);
}

char	*chars_inside_quotes(int *count, char *read, char c)
{
	read++;
	*count += 1;
	while (*read && *read != c)
	{
		*count += 1;
		read++;
	}
	return (read);
}

int	howmany_words(char *s)
{
	int	i;
	int	counter;

	i = 0;
	i = skip_space(s);
	counter = 0;
	while (s[i])
	{
		if (s[i] == 39 || s[i] == 34)
		{
			if (s[i] == 39)
				chars_inside_quotes(&i, (s + i), 39);
			else
				chars_inside_quotes(&i, (s + i), 34);
		}
		if (s[i] && ft_iswhitespace(s[i]) && s[i + 1] != '\0'
			&& !ft_iswhitespace(s[i + 1]))
			counter++;
		i++;
	}
	counter++;
	return (counter);
}

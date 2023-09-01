/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoumni <tmoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 20:20:26 by tmoumni           #+#    #+#             */
/*   Updated: 2023/08/21 09:08:24 by tmoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

static size_t	count_words(char const *s, char c)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		while (*s == c && *(s + 1))
			s++;
		if (*s != c && (*(s + 1) == c || *(s + 1) == '\0'))
			count++;
		s++;
	}
	return (count);
}

static size_t	word_len(char const *s, int c)
{
	size_t	count;

	count = 0;
	while (s[count] && s[count] != c)
		count++;
	return (count);
}

static void	*free_mem(char **array)
{
	size_t	j;

	j = 0;
	while (array[j])
	{
		free(array[j]);
		j++;
	}
	free(array);
	return (NULL);
}

static char const	*skip_delimiter(char const *s, char c)
{
	while (*s && *s == c)
		s++;
	return (s);
}

char	**ft_split(char const *s, char c)
{
	char	**array;
	size_t	index;
	size_t	count;
	size_t	words;

	if (!s || !(*s))
		return (NULL);
	index = -1;
	words = count_words(s, c);
	array = (char **)malloc((count_words(s, c) + 1) * sizeof(char *));
	if (!array)
		return (NULL);
	while (++index < words)
	{
		s = skip_delimiter(s, c);
		array[index] = (char *)malloc((word_len(s, c) + 1) * sizeof(char));
		if (!array[index])
			return (free_mem(array));
		count = 0;
		while (*s && *s != c)
			array[index][count++] = *s++;
		array[index][count] = '\0';
	}
	array[index] = NULL;
	return (array);
}

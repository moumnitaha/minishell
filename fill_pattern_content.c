/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_pattern_content.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyassine <eyassine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 16:35:01 by eyassine          #+#    #+#             */
/*   Updated: 2023/08/31 18:27:39 by eyassine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

int	count_word(char *s, int del)
{
	int	i;
	int	s_quote;
	int	d_quote;
	int	counter;

	i = 0;
	s_quote = 0;
	d_quote = 0;
	counter = 0;
	while (s[i])
	{
		check_for_quotes(s[i], &s_quote, &d_quote);
		if (s[i] == del && !s_quote)
			counter++;
		i++;
	}
	return (counter);
}

int	pattern_len(char *s, int *i)
{
	int	len;
	int	s_q;
	int	d_q;

	s_q = 0;
	d_q = 0;
	while (s[*i])
	{
		check_for_quotes(s[*i], &s_q, &d_q);
		if (s[*i] == '$' && !s_q)
		{
			len = 0;
			*i += 1;
			while (s[*i])
			{
				if (expand_delim(s[*i]))
					return (len);
				len++;
				*i += 1;
			}
			return (len);
		}
		*i += 1;
	}
	return (0);
}

void	ft_fill_pat_cont(char *content, char **patterns)
{
	int	s_q;
	int	d_q;
	int	i;

	s_q = 0;
	d_q = 0;
	i = 0;
	while (*content && patterns[i])
	{
		check_for_quotes(*content, &s_q, &d_q);
		if (*content == '$' && !s_q)
		{
			content++;
			if (!*content || *content == '=' || *content == '?')
				content = no_expand((--content), patterns[i]);
			else
				content = insert_path_cont(content, patterns[i]);
			i++;
		}
		if (*content)
			content++;
	}
}

char	*insert_path_cont(char *cont, char *patterns)
{
	int	i;

	i = 0;
	while (*cont)
	{
		if (expand_delim(*cont))
		{
			cont--;
			if (*cont == '$')
				patterns[i++] = *cont;
			break ;
		}
		patterns[i] = *cont;
		i++;
		cont++;
	}
	patterns[i] = '\0';
	return (cont);
}

char	**fill_pattern_content(char *content)
{
	int		i;
	int		j;
	int		len;
	char	**patterns;

	i = 0;
	j = 0;
	len = count_word(content, '$');
	patterns = malloc(sizeof(char *) * (len + 1));
	if (!patterns)
		return (NULL);
	patterns[len] = NULL;
	while (i < count_word(content, '$'))
	{
		len = pattern_len(content, &j);
		patterns[i] = malloc(sizeof(char) * (len + 3));
		if (!patterns[i])
			return (NULL);
		patterns[i][len] = '\0';
		i++;
	}
	i = 0;
	ft_fill_pat_cont(content, patterns);
	return (patterns);
}

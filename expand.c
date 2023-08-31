/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoumni <tmoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 23:08:29 by eyassine          #+#    #+#             */
/*   Updated: 2023/08/31 16:18:44 by tmoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

int	check_expand(char *cont)
{
	int	i;
	int	s_q;
	int	d_q;

	s_q = 0;
	d_q = 0;
	if (!cont)
		return (0);
	i = 0;
	while (cont[i])
	{
		check_for_quotes(cont[i], &s_q, &d_q);
		if (cont[i] == '$' && !s_q)
			return (1);
		i++;
	}
	return (0);
}

char	*no_expand(char *content, char *patt)
{
	int	i;

	i = 0;
	while (*content)
	{
		if (*content == '?' || *content == '=')
		{
			patt[i++] = *content;
			break ;
		}
		patt[i] = *content;
		content++;
		i++;
	}
	patt[i] = '\0';
	return (content);
}

char	*ft_expand(char *content, char **env)
{
	char	*new;
	char	**pattern;
	char	**value;

	new = NULL;
	pattern = fill_pattern_content(content);
	if (!pattern)
		return (content);
	value = fill_pattern_value(pattern, env);
	if (!value)
	{
		free(pattern);
		return (content);
	}
	new = ft_expanded_content(value, pattern, content);
	if (!new)
	{
		free(pattern);
		free(value);
		return (content);
	}
	ft_free_arr(pattern);
	free(value);
	free(content);
	return (new);
}

void	expand(t_list *list, char **env)
{
	t_list	*begin;

	begin = list;
	while (list)
	{
		if (check_expand(list->content))
		{
			if (list->prev && list->prev->tokens != HEREDOC)
				list->content = ft_expand(list->content, env);
			else if (!list->prev)
				list->content = ft_expand(list->content, env);
		}
		list = list->next;
	}
	expand_exit_status(begin);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanded_content.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyassine <eyassine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 16:50:54 by eyassine          #+#    #+#             */
/*   Updated: 2023/08/31 18:30:41 by eyassine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

void	ft_stcpy(char *new, int *j, char *value)
{
	int	i;

	i = 0;
	while (value[i])
	{
		new[*j] = value[i];
		i++;
		*j += 1;
	}
}

int	expand_delim(char c)
{
	if (!(c >= 48 && c <= 57)
		&& !(c >= 65 && c <= 90)
		&& !(c >= 97 && c <= 122) && c != 95)
		return (1);
	else
		return (0);
}

void	fill_expanded_content(char *s, char **value, char *new, char **pattern)
{
	t_fill_exp	exp;

	exp.s_q = 0;
	exp.d_q = 0;
	exp.i = 0;
	exp.j = 0;
	exp.pat_i = 0;
	while (s[exp.i])
	{
		check_for_quotes(s[exp.i], &exp.s_q, &exp.d_q);
		if (s[exp.i] == '$' && !exp.s_q)
		{
			if (value[exp.pat_i][0] == '$')
				exp.i--;
			ft_stcpy(new, &exp.j, value[exp.pat_i]);
			exp.i += (ft_strlen(pattern[exp.pat_i]));
			exp.pat_i++;
		}
		else
			new[exp.j++] = s[exp.i];
		exp.i++;
	}
	new[exp.j] = '\0';
}

char	*ft_expanded_content(char **value, char **pattern, char *s)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	while (value[i])
	{
		j += ft_strlen(value[i]);
		i++;
	}
	new = malloc(sizeof(char) * (ft_strlen(s) + (j + 1)));
	fill_expanded_content(s, value, new, pattern);
	return (new);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   len_without_quote.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyassine <eyassine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 17:01:12 by eyassine          #+#    #+#             */
/*   Updated: 2023/08/17 10:56:34 by eyassine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

char	*count_(char *s, int *s_q, int *d_q, int *len)
{
	if (*s_q)
	{
		s++;
		while (*s && *s != 39)
			s++;
		*len += 2;
		*s_q = 0;
	}
	else if (*d_q)
	{
		s++;
		while (*s && *s != 34)
			s++;
		*len += 2;
		*d_q = 0;
	}
	if (!*s)
		s--;
	return (s);
}

int	len_without_quotes(char *s)
{
	int	len;
	int	s_q;
	int	d_q;

	len = 0;
	s_q = 0;
	d_q = 0;
	while (*s)
	{
		if (*s == 34 || *s == 39)
		{
			if (*s == 39)
				s_q = 1;
			else
				d_q = 1;
		}
		s = count_(s, &s_q, &d_q, &len);
		s++;
	}
	return (len);
}

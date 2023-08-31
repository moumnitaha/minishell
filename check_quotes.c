/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoumni <tmoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 17:57:15 by eyassine          #+#    #+#             */
/*   Updated: 2023/08/25 16:19:31 by tmoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

char	*within_quotes(char *read, int *duble, int *single)
{
	char	quote;

	quote = *read;
	read++;
	if (quote == 34)
		*duble += 1;
	else
		*single += 1;
	while (*read)
	{
		if (*read == quote)
		{
			if (quote == 34)
				*duble += 1;
			else
				*single += 1;
			return (read);
		}
		read++;
	}
	return (read);
}

int	check_quotes(char *read)
{
	int	duble;
	int	single;

	if (!read)
		return (0);
	duble = 0;
	single = 0;
	while (*read)
	{
		if (*read == 34 || *read == 39)
			read = within_quotes(read, &duble, &single);
		if (*read)
			read++;
	}
	if (duble % 2 != 0 || single % 2 != 0)
	{
		write(2, "ERROR unclosed quote\n", 22);
		g_msh.exit_status = 258;
		return (0);
	}
	return (1);
}

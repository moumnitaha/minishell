/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyassine <eyassine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 15:12:35 by tmoumni           #+#    #+#             */
/*   Updated: 2023/08/28 16:24:56 by eyassine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

int	ft_iswhitespace(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

static int	count_digits(const char *str)
{
	int	index;
	int	count;

	index = 0;
	count = 0;
	while (!ft_isalnum(str[index]))
		index++;
	while (!(str[index] - '0'))
		index++;
	while (ft_isdigit(str[index++]))
		count++;
	return (count);
}

int	ft_atoi(const char *str)
{
	int		sign;
	int		index;
	long	result;

	index = 0;
	sign = 1;
	result = 0;
	while (str[index] && ft_iswhitespace(str[index]))
		index++;
	if (str[index] == '+' || str[index] == '-')
		index++;
	if (index > 0 && str[index - 1] == '-')
		sign = -1;
	while (str[index] && ft_isdigit(str[index]))
		result = result * 10 + (str[index++] - '0');
	if (result < 0 || count_digits(str) > 19)
	{
		if (sign == 1)
			return (-1);
		return (0);
	}
	return (sign * result);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoumni <tmoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 11:52:54 by tmoumni           #+#    #+#             */
/*   Updated: 2023/08/18 17:47:45 by tmoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

static char	*gen_nbr(char *nbr, long long n, int div, int count)
{
	int	index;

	index = 0;
	if (n < 0)
	{
		nbr[0] = '-';
		n *= -1;
		index++;
		count++;
	}
	while (index < count)
	{
		nbr[index] = (n / div) + '0';
		n = n % div;
		div = div / 10;
		index++;
	}
	nbr[index] = '\0';
	return (nbr);
}

char	*ft_itoa(int n)
{
	char		*nbr;
	int			count;
	int			div;
	long long	nb;

	count = 1;
	div = 1;
	nb = (long long)n;
	while ((nb / div >= 10) || (nb / div <= -10))
	{
		div *= 10;
		count++;
	}
	if (n < 0)
		nbr = (char *)malloc((count + 2) * sizeof(char));
	else
		nbr = (char *)malloc((count + 1) * sizeof(char));
	if (!nbr)
		return (NULL);
	nbr = gen_nbr(nbr, nb, div, count);
	return (nbr);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoumni <tmoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 19:01:49 by tmoumni           #+#    #+#             */
/*   Updated: 2023/08/02 17:21:27 by tmoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

char	*ft_strdup(const char *s)
{
	char	*ptr;
	int		count;

	count = 0;
	ptr = (char *)malloc((ft_strlen((char *)s) + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	while (count < ft_strlen((char *)s))
	{
		ptr[count] = s[count];
		count++;
	}
	ptr[count] = '\0';
	return (ptr);
}

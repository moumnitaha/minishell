/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoumni <tmoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 13:31:19 by tmoumni           #+#    #+#             */
/*   Updated: 2023/08/22 17:33:57 by tmoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

void	ft_pwd(void)
{
	char	*pwd;

	if (ft_get_env("PWD"))
		printf("%s\n", ft_get_env("PWD"));
	else
	{
		pwd = malloc(PATH_MAX);
		if (!pwd)
			return ;
		getcwd(pwd, PATH_MAX);
		ft_putstr_fd(pwd, 1);
		ft_putstr_fd("\n", 1);
		free(pwd);
	}
}

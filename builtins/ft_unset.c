/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoumni <tmoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 17:45:37 by tmoumni           #+#    #+#             */
/*   Updated: 2023/08/31 19:53:28 by tmoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

int	valid_idei(char *str)
{
	int	i;

	i = 0;
	if (ft_isdigit((char)(str[0])))
		return (0);
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	ft_prt_erri(char *name)
{
	if (!valid_idei(name) || !ft_strlen(name))
	{
		ft_put_error(name, " not a valid identifier");
		g_msh.exit_status = 1;
		return (1);
	}
	return (0);
}

void	ft_unset(char **cmd)
{
	if (!*(cmd + 1))
		return ;
	cmd++;
	while (*cmd)
	{
		if (!ft_prt_erri(*cmd))
		{
			ft_lst_delete_node(&g_msh.env, *cmd);
			g_msh.exit_status = 0;
		}
		cmd++;
	}
}

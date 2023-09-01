/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoumni <tmoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 14:01:14 by tmoumni           #+#    #+#             */
/*   Updated: 2023/08/28 18:33:17 by tmoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

int	is_arg(char *str)
{
	if (!str || !(*str))
		return (0);
	if (*str == '-' && *(str + 1))
		str++;
	else
		return (0);
	while (*str == 'n')
		str++;
	if (*str)
		return (0);
	return (1);
}

void	check_all_string(char *cmd, int fd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '$' && cmd[i + 1] == '?')
		{
			i += 1;
			ft_putnbr_fd(g_msh.exit_status, fd);
		}
		else
			ft_putchar_fd(cmd[i], fd);
		i += 1;
	}
}

void	ft_echo(char **cmd, int fd)
{
	int		nl;

	cmd++;
	nl = is_arg(*cmd);
	if (nl)
	{
		while (is_arg(*cmd))
			cmd++;
	}
	while (*cmd)
	{
		if (*cmd)
		{
			ft_putstr_fd(*cmd, fd);
			if (*(cmd + 1))
				ft_putstr_fd(" ", fd);
		}
		cmd++;
	}
	if (!nl)
		ft_putstr_fd("\n", fd);
	g_msh.exit_status = 0;
}

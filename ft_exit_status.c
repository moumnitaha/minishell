/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_status.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoumni <tmoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 15:01:55 by tmoumni           #+#    #+#             */
/*   Updated: 2023/08/28 22:56:45 by tmoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

int	update_exit_status(int status)
{
	if (WIFSTOPPED(status))
		return (FATAL_SIGNAL + WSTOPSIG(status));
	if (WIFSIGNALED(status))
	{
		if (FATAL_SIGNAL + WTERMSIG(status) == 130)
			ft_putstr_fd("\n", 2);
		else if (FATAL_SIGNAL + WTERMSIG(status) == 131)
			ft_putstr_fd("Quit: 3\n", 2);
		return (FATAL_SIGNAL + WTERMSIG(status));
	}
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}

void	exit_dir(char *cmd)
{
	ft_put_error(cmd, "is a directory");
	exit(126);
}

void	exit_cmd(char *cmd)
{
	ft_put_error(cmd, "command not found");
	exit(127);
}

int	has_dollar(char *str)
{
	int	i;

	i = 0;
	if (!str || !(*str))
		return (-1);
	while (*str && str[i])
	{
		if (str[i] == '$')
			return (i);
		i++;
	}
	return (-1);
}

void	reset_std(void)
{
	dup2(g_msh.standard_in, STDIN_FILENO);
	dup2(g_msh.standard_out, STDOUT_FILENO);
}

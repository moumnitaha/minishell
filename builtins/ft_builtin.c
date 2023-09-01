/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoumni <tmoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 22:08:44 by tmoumni           #+#    #+#             */
/*   Updated: 2023/08/23 13:10:30 by tmoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

bool	is_builtin(t_cmd *t_cmd)
{
	if (t_cmd->cmd && ft_strmatch(t_cmd->cmd[0], "echo"))
		return (true);
	else if (t_cmd->cmd && ft_strmatch(t_cmd->cmd[0], "cd"))
		return (true);
	else if (t_cmd->cmd && ft_strmatch(t_cmd->cmd[0], "pwd"))
		return (true);
	else if (t_cmd->cmd && ft_strmatch(t_cmd->cmd[0], "exit"))
		return (true);
	else if (t_cmd->cmd && ft_strmatch(t_cmd->cmd[0], "export"))
		return (true);
	else if (t_cmd->cmd && ft_strmatch(t_cmd->cmd[0], "env"))
		return (true);
	else if (t_cmd->cmd && ft_strmatch(t_cmd->cmd[0], "unset"))
		return (true);
	return (false);
}

int	tab_zise(char **tab)
{
	int	length;

	length = 0;
	while (tab[length])
		length++;
	return (length);
}

void	check_exit(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] < '0' || cmd[i] > '9')
		{
			ft_put_error("exit", "numeric argument required");
			exit(255);
		}
		i++;
	}
}

void	ft_exit(t_cmd *t_cmd)
{
	if (g_msh.cmd_nbrs == 1)
		write(1, "exit\n", 6);
	if (t_cmd->cmd[1])
		check_exit(t_cmd->cmd[1]);
	if (tab_zise(t_cmd->cmd) > 2)
	{
		ft_put_error("exit", "too many arguments");
		g_msh.exit_status = 1;
	}
	else if (t_cmd->cmd[1])
		exit(ft_atoi(t_cmd->cmd[1]));
	else
		exit(0);
}

void	builtin_exec(t_cmd *t_cmd)
{
	if (t_cmd->cmd && ft_strmatch(t_cmd->cmd[0], "echo"))
		ft_echo(t_cmd->cmd, 1);
	else if (t_cmd->cmd && ft_strmatch(t_cmd->cmd[0], "cd"))
		ft_cd(t_cmd->cmd);
	else if (t_cmd->cmd && ft_strmatch(t_cmd->cmd[0], "pwd"))
		ft_pwd();
	else if (t_cmd->cmd && ft_strmatch(t_cmd->cmd[0], "exit"))
		ft_exit(t_cmd);
	else if (t_cmd->cmd && ft_strmatch(t_cmd->cmd[0], "export"))
		ft_export(t_cmd->cmd);
	else if (t_cmd->cmd && ft_strmatch(t_cmd->cmd[0], "env"))
		print_env(0);
	else if (t_cmd->cmd && ft_strmatch(t_cmd->cmd[0], "unset"))
		ft_unset(t_cmd->cmd);
}

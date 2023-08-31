/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoumni <tmoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 19:49:55 by tmoumni           #+#    #+#             */
/*   Updated: 2023/08/31 17:24:43 by tmoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

void	run_parent(pid_t pid, int *p_r_e, int pipes_fd[2], t_cmd *cmd)
{
	int	status;

	status = 0;
	if (*p_r_e != -1)
		close(*p_r_e);
	if (g_msh.cmd_index < commands_nbr(g_msh.t_cmd) - 1)
	{
		close(pipes_fd[1]);
		*p_r_e = pipes_fd[0];
	}
	if (cmd->redirec)
		waitpid(pid, &status, 0);
	g_msh.exit_status = update_exit_status(status);
}

int	ft_pipe(int pipes_fd[2], int cmd_index, int cmd_nbrs)
{
	if (cmd_index < cmd_nbrs - 1)
	{
		if (pipe(pipes_fd) == -1)
		{
			perror("pipe creation failed");
			exit(EXIT_FAILURE);
		}
	}
	return (0);
}

void	close_fd(int p_r_e, pid_t *pid, t_cmd *commands)
{
	int		i;
	int		status;

	status = 0;
	i = 0;
	while (commands)
	{
		if (!commands->redirec)
		{
			waitpid(pid[i], &status, 0);
			if (pid[i] == -1)
			{
				g_msh.exit_status = 1;
				break ;
			}
			g_msh.exit_status = update_exit_status(status);
		}
		i++;
		commands = commands->next;
	}
	free(pid);
	if (p_r_e != -1)
		close(p_r_e);
}

void	handle_exec(t_cmd *commands, int cmd_index, int pipes_fd[2], int p_r_e)
{
	while (commands != NULL && g_msh.cmd_nbrs)
	{
		ft_pipe(pipes_fd, cmd_index, g_msh.cmd_nbrs);
		g_msh.pid[cmd_index] = fork();
		if (g_msh.pid[cmd_index] == -1)
		{
			ft_put_error("fork", "Resource temporarily unavailable");
			break ;
		}
		if (g_msh.pid[cmd_index] == 0)
		{
			child_sig();
			run_child(commands, pipes_fd, cmd_index, p_r_e);
		}
		else
		{
			parent_sig();
			run_parent(g_msh.pid[cmd_index], &p_r_e, pipes_fd, commands);
		}
		g_msh.cmd_index = ++cmd_index;
		commands = commands->next;
	}
}

void	exec_pipes(t_cmd *commands)
{
	int		prev_read_end;
	int		pipes_fd[2];
	int		cmd_index;

	cmd_index = 0;
	g_msh.cmd_nbrs = commands_nbr(commands);
	prev_read_end = -1;
	g_msh.pid = malloc(sizeof(pid_t) * g_msh.cmd_nbrs);
	if (!g_msh.pid)
		return ;
	handle_exec(commands, cmd_index, pipes_fd, prev_read_end);
	close_fd(prev_read_end, g_msh.pid, commands);
}

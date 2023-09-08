/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_help.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoumni <tmoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 16:42:04 by tmoumni           #+#    #+#             */
/*   Updated: 2023/09/08 11:33:53 by tmoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

int	check_cmd(char	**cmd)
{
	DIR	*dir;

	if (!ft_strlen(*cmd))
		return (0);
	if (ft_strmatch(*cmd, "."))
	{
		ft_put_error(*cmd, "filename argument required");
		write(2, ".: usage: . filename [arguments]\n", 34);
		exit(2);
	}
	dir = opendir(*cmd);
	if (dir != NULL)
	{
		free(dir);
		if (!ft_strncmp(*cmd, "./", 2) || (*cmd)[ft_strlen(*cmd) - 1] == '/')
			exit_dir(*cmd);
		else
			exit_cmd(*cmd);
	}
	free(dir);
	if (!ft_strncmp(*cmd, "./", 2) || *cmd[0] == '/')
		return (0);
	return (1);
}

char	*fix_cmd(t_cmd *cmd_ptr)
{
	char	*cmd;
	char	*prefixed;
	char	**path;
	int		i;

	if (!cmd_ptr->cmd || !cmd_ptr->cmd[0])
		return (NULL);
	i = 0;
	path = ft_split(ft_get_env("PATH"), ':');
	if (!path)
		return (*cmd_ptr->cmd);
	while (path[i])
	{
		cmd = *cmd_ptr->cmd;
		if (!check_cmd(&cmd))
			break ;
		prefixed = ft_strjoin("/", cmd);
		cmd = ft_strjoin(path[i], prefixed);
		free(prefixed);
		if (!access(cmd, F_OK) && !access(cmd, X_OK))
			break ;
		free(cmd);
		i++;
	}
	if (!path[i] && access(cmd, X_OK))
		return (*cmd_ptr->cmd);
	free_tab(path);
	return (cmd);
}

int	has_s(char *cmd)
{
	while (*cmd)
	{
		if (*cmd == '/')
			return (1);
		cmd++;
	}
	return (0);
}

int	ft_execve(char *cmd, t_cmd *cmd_ptr, char **env)
{
	execve(cmd, cmd_ptr->cmd, env);
	free_tab(env);
	dup2(g_msh.standard_out, STDOUT_FILENO);
	dup2(g_msh.standard_in, STDIN_FILENO);
	if (errno == ENOENT)
	{
		if (has_s(cmd))
			ft_put_error(cmd, "No such file or directory");
		else
			ft_put_error(cmd, "command not found");
		exit(CMD_N_FOUND);
	}
	if (errno == EACCES)
	{
		ft_put_error(cmd, "Permission denied");
		exit(NOT_EXEC);
	}
	if (ft_strncmp(cmd, "./", 2))
		free(cmd);
	exit(EXIT_FAILURE);
}

void	run_child(t_cmd *cmd_ptr, int pipes_fd[2], int cmd_index, int p_r_e)
{
	char	*cmd;
	char	**env;

	cmd = fix_cmd(cmd_ptr);
	env = ft_list_to_tab(g_msh.env);
	ft_handle_redirections(cmd_ptr->redirec);
	if (p_r_e != -1 && g_msh.fd_in == -1)
		dup2(p_r_e, STDIN_FILENO);
	else
		dup2(g_msh.fd_in, STDIN_FILENO);
	if (cmd_index < commands_nbr(g_msh.t_cmd) - 1)
	{
		if (g_msh.fd_out != -1)
			dup2(g_msh.fd_out, STDOUT_FILENO);
		else
			dup2(pipes_fd[1], STDOUT_FILENO);
		close(pipes_fd[0]);
		close(pipes_fd[1]);
	}
	if (is_builtin(cmd_ptr))
		builtin_exec(cmd_ptr);
	else if (cmd)
		ft_execve(cmd, cmd_ptr, env);
	free_tab(env);
	exit(0);
}

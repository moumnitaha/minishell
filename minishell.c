/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoumni <tmoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 22:12:08 by tmoumni           #+#    #+#             */
/*   Updated: 2023/08/31 17:04:31 by tmoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

void	free_mem(t_list *head, char *read, char **env)
{
	ft_free_list(head);
	free(read);
	free_tab(env);
}

void	handle_head(t_list *head, char **env, char *read)
{
	tokenize_list(head);
	head = split_operator(head);
	expand(head, env);
	head = check_expanded_value(head);
	if (!check_syntax(head) || !*read || !head)
	{
		free_mem(head, read, env);
		return ;
	}
	delete_quotes(head);
	g_msh.t_cmd = build_command(head);
	if (!(g_msh.t_cmd))
		return ;
	if (commands_nbr(g_msh.t_cmd) <= 1 && is_builtin(g_msh.t_cmd)
		&& !(g_msh.t_cmd->redirec))
	{
		ft_handle_redirections(g_msh.t_cmd->redirec);
		builtin_exec(g_msh.t_cmd);
	}
	else
		exec_pipes(g_msh.t_cmd);
	free_mem(head, read, env);
	ft_free_cmd(g_msh.t_cmd);
	g_msh.cmd_index = 0;
	reset_std();
}

void	minishell(char **env, char *read)
{
	t_list	*head;

	while (1)
	{
		signal(SIGINT, handle_ctrl_c);
		signal(SIGQUIT, handle_back_s);
		read = readline("minishell-$ ");
		env = ft_list_to_tab(g_msh.env);
		if (!read)
			exit_with(g_msh.exit_status);
		if (*read)
			add_history(read);
		if (!check_quotes(read))
		{
			free(read);
			continue ;
		}
		head = lexer(read);
		if (!head)
			return ;
		handle_head(head, env, read);
	}
}

void	init_g_msh(void)
{
	g_msh.standard_out = dup(STDOUT_FILENO);
	g_msh.standard_in = dup(STDIN_FILENO);
	g_msh.fd_in = -1;
	g_msh.fd_out = -1;
	g_msh.is_runing = 0;
	g_msh.cmd_index = 0;
	g_msh.cmd_nbrs = 0;
	g_msh.exit_status = 0;
	g_msh.here = 0;
}

int	main(int ac, char **av, char **env)
{
	char	*read;

	read = NULL;
	(void)av;
	if (ac > 1)
		return (1);
	rl_catch_signals = 0;
	ft_env_init(env);
	init_g_msh();
	minishell(env, read);
	return (0);
}

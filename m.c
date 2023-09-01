/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoumni <tmoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 18:14:41 by eyassine          #+#    #+#             */
/*   Updated: 2023/08/28 18:32:45 by tmoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

t_msh	g_msh;

void	ft_free_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;

	while (cmd)
	{
		tmp = cmd;
		cmd = cmd->next;
		if (tmp->redirec)
			ft_free_list(tmp->redirec);
		if (tmp->cmd)
			ft_free_arr(tmp->cmd);
		free(tmp);
	}
}

int	commands_nbr(t_cmd *cmd)
{
	t_cmd	*head;
	int		length;

	head = cmd;
	length = 0;
	while (head)
	{
		length++;
		head = head->next;
	}
	return (length);
}

void	handle_ctrl_c(int signal)
{
	(void)signal;
	g_msh.exit_status = 130;
	if (g_msh.here == 0)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	handle_back_s(int signal)
{
	(void)signal;
	if (g_msh.here == 0)
	{
		rl_redisplay();
	}
}

void	print_cmd(t_cmd *head)
{
	int		i;
	t_list	*tmp;

	i = 0;
	while (head)
	{
		i = 0;
		printf(RED"---------"END"\n");
		while (head->cmd && head->cmd[i])
		{
			printf(GREEN"cmd |%s|"END"\n", head->cmd[i]);
			i++;
		}
		tmp = head->redirec;
		while (tmp)
		{
			printf(CYAN"file name |%s|"END"\t", tmp->content);
			printf(CYAN"tokens |%d|"END"\t", tmp->tokens);
			printf(CYAN"quotes |%d|"END"\n", tmp->any_quotes);
			tmp = tmp->next;
		}
		head = head->next;
	}
	printf(RED"---------"END"\n");
}

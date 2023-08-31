/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_help.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoumni <tmoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 15:20:08 by tmoumni           #+#    #+#             */
/*   Updated: 2023/08/28 19:04:03 by tmoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

void	edit_node(t_env **env, char *name, char *value, int inc)
{
	t_env	*head;
	char	*tmp;

	head = *env;
	while (head)
	{
		if (ft_strmatch(head->name, name))
		{
			tmp = head->value;
			if (inc)
				head->value = ft_strjoin(head->value, value);
			else
				head->value = ft_strdup(value);
			free(tmp);
			head->equal = true;
		}
		head = head->next;
	}
	free(name);
	free(value);
}

void	handle(int signal)
{
	(void)signal;
	write(1, "\n", 1);
	exit(1);
}

void	handle_s(int signal)
{
	(void)signal;
	rl_on_new_line();
	rl_redisplay();
}

void	child_sig(void)
{
	signal(SIGINT, handle_ctrl_c);
	signal(SIGQUIT, handle_back_s);
}

void	parent_sig(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

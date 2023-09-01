/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_exit_status.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyassine <eyassine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 14:45:33 by eyassine          #+#    #+#             */
/*   Updated: 2023/08/31 19:39:19 by eyassine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

char	*allocate_new(t_list *t_cmd, char *cmd, char *value, int exit_s_n)
{
	char	*new;

	new = malloc(sizeof(char) * ft_strlen(cmd)
			+ (ft_strlen(value) * exit_s_n));
	if (!new)
	{
		ft_free_list(t_cmd);
		exit(1);
	}
	return (new);
}

int	check_exit_status(char *cmd, t_list *list)
{
	int	exit_status;
	int	s_q;
	int	d_q;

	exit_status = 0;
	d_q = 0;
	s_q = 0;
	if (list->prev && list->prev->tokens == HEREDOC)
		return (exit_status);
	while (*cmd)
	{
		check_for_quotes(*cmd, &s_q, &d_q);
		if (*cmd == '$' && *(cmd + 1) == '?' && !s_q)
			exit_status++;
		cmd++;
	}
	return (exit_status);
}

void	init(t_fill_exp *exp)
{
	exp->i = 0;
	exp->j = 0;
	exp->d_q = 0;
	exp->s_q = 0;
}

char	*expand_exit(int exit_status_nb, char *cmd, char *value, t_list *begin)
{
	t_fill_exp	exp;
	char		*new;

	init(&exp);
	new = allocate_new(begin, cmd, value, exit_status_nb);
	while (cmd[exp.i])
	{
		check_for_quotes(cmd[exp.i], &exp.s_q, &exp.d_q);
		if (cmd[exp.i] == '$' && cmd[exp.i + 1] == '?' && !exp.s_q)
		{
			exp.pat_i = 0;
			exp.i++;
			while (value[exp.pat_i])
				new[exp.j++] = value[exp.pat_i++];
		}
		else
			new[exp.j++] = cmd[exp.i];
		exp.i++;
	}
	new[exp.j] = '\0';
	free(cmd);
	free(value);
	return (new);
}

void	expand_exit_status(t_list *list)
{
	int		i;
	int		exit_status;
	char	*exit_value;
	t_list	*begin;

	begin = NULL;
	while (list)
	{
		i = 0;
		while (list->content && list->content[i])
		{
			exit_status = check_exit_status(list->content, list);
			if (exit_status)
			{
				exit_value = ft_itoa(g_msh.exit_status);
				if (!exit_value)
					exit(1);
				list->content = expand_exit(exit_status, list->content,
						exit_value, begin);
			}
			i++;
		}
		list = list->next;
	}
}

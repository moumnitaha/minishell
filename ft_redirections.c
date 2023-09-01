/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoumni <tmoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 14:57:50 by tmoumni           #+#    #+#             */
/*   Updated: 2023/08/28 14:47:37 by tmoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

void	handle_out_rdr(t_list *r_head, int fd_out)
{
	fd_out = open(r_head->content, O_CREAT | O_RDWR | O_TRUNC, 0000755);
	if (fd_out == -1)
	{
		ft_put_error(r_head->content, "No such file or directory");
		exit(EXIT_FAILURE);
	}
	if (g_msh.cmd_index < g_msh.cmd_nbrs - 1)
		g_msh.fd_out = dup(fd_out);
	else
		dup2(fd_out, STDOUT_FILENO);
	close(fd_out);
}

void	handle_in_rdr(t_list *r_head, int fd_in)
{
	fd_in = open(r_head->content, O_RDONLY, 0000755);
	if (fd_in == -1)
	{
		ft_put_error(r_head->content, "No such file or directory");
		exit(EXIT_FAILURE);
	}
	else
	{
		if (g_msh.cmd_nbrs <= 1)
			dup2(fd_in, STDIN_FILENO);
		else
			g_msh.fd_in = dup(fd_in);
		g_msh.exit_status = 0;
	}
	if (fd_in != -1)
		close(fd_in);
}

void	handle_in_app(t_list *r_head, int fd_out)
{
	fd_out = open(r_head->content, O_CREAT | O_RDWR | O_APPEND, 0000755);
	if (fd_out == -1)
	{
		ft_put_error(r_head->content, "No such file or directory");
		exit(EXIT_FAILURE);
	}
	dup2(fd_out, STDOUT_FILENO);
}

void	ft_handle_redirections(t_list *r_head)
{
	int		fd_out;
	int		fd_in;
	t_list	*head;

	fd_out = 0;
	fd_in = 0;
	head = r_head;
	while (head != NULL)
	{
		if (head->tokens == HEREDOC)
			handle_herdoc(head);
		head = head->next;
	}
	head = r_head;
	while (head != NULL)
	{
		if (head->tokens == OUT_REDIREC)
			handle_out_rdr(head, fd_out);
		if (head->tokens == APP)
			handle_in_app(head, fd_out);
		if (head->tokens == IN_REDIREC)
			handle_in_rdr(head, fd_in);
		head = head->next;
	}
}

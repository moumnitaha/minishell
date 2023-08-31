/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoumni <tmoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 20:14:45 by tmoumni           #+#    #+#             */
/*   Updated: 2023/08/31 20:06:12 by tmoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

int	check_line(char *line, char *content)
{
	if (!line || ft_strmatch(line, content))
	{
		free (line);
		return (0);
	}
	return (1);
}

int	end_index(char *str, int start)
{
	int		i;

	i = start + 1;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_' && str[i] != '?')
			return (i);
		i++;
	}
	return (ft_strlen(str));
}

char	*expand_into_str(char *str)
{
	char	*sub;
	char	*sub2;
	char	*line;
	char	*env;
	int		end;

	end = end_index(str, has_dollar(str));
	sub = ft_substr(str, has_dollar(str) + 1, end - has_dollar(str) - 1);
	if (ft_get_env(sub))
		env = ft_strdup(ft_get_env(sub));
	else if (ft_strmatch(sub, "?"))
		env = ft_itoa(g_msh.exit_status);
	else
		env = ft_strdup("");
	free(sub);
	sub2 = ft_substr(str, 0, has_dollar(str));
	sub = ft_strjoin(sub2, env);
	free(sub2);
	sub2 = ft_substr(str, end, ft_strlen(str) - end);
	line = ft_strjoin(sub, sub2);
	ft_free_sub(sub, sub2, env);
	if (has_dollar(line) != -1)
		line = expand_into_str(line);
	return (free(str), line);
}

void	handle_pipes(int pipe_fd[2], int p)
{
	if (p == 1)
	{
		if (pipe(pipe_fd) == -1)
		{
			perror("Pipe creation failed");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		close(pipe_fd[1]);
		close(pipe_fd[0]);
	}
}

void	handle_herdoc(t_list *r_head)
{
	char	*line;
	int		pipe_fd[2];

	rl_catch_signals = 1;
	signal(SIGINT, handle);
	signal(SIGQUIT, handle_s);
	if (!r_head->tokens || r_head->tokens != HEREDOC)
		return ;
	handle_pipes(pipe_fd, 1);
	dup2(g_msh.standard_out, STDOUT_FILENO);
	dup2(g_msh.standard_in, STDIN_FILENO);
	while (1)
	{
		line = readline("hdoc> ");
		if (!check_line(line, r_head->content))
			break ;
		if (has_dollar(line) != -1 && !r_head->any_quotes)
			line = expand_into_str(line);
		write(pipe_fd[1], line, ft_strlen(line));
		write(pipe_fd[1], "\n", 1);
		free(line);
	}
	dup2(pipe_fd[0], STDIN_FILENO);
	g_msh.fd_in = dup(STDIN_FILENO);
	handle_pipes(pipe_fd, 0);
}

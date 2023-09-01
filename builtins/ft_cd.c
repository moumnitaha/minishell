/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoumni <tmoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 17:20:55 by tmoumni           #+#    #+#             */
/*   Updated: 2023/08/23 12:51:20 by tmoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

char	*ft_get_pwd(void)
{
	char	*str;

	str = malloc(PATH_MAX);
	if (!str)
		return (NULL);
	getcwd(str, PATH_MAX);
	return (str);
}

void	ft_update_pwd(char *path)
{
	t_env	*head;

	head = g_msh.env;
	while (head != NULL) 
	{
		if (ft_strmatch(head->name, "PWD"))
		{
			free(head->value);
			head->value = ft_strdup(path);
			break ;
		}
		head = head->next;
	}
	free(path);
}

void	ft_update_oldpwd(char *old_path)
{
	t_env	*head;

	head = g_msh.env;
	while (head != NULL)
	{
		if (ft_strmatch(head->name, "OLDPWD"))
		{
			free(head->value);
			head->value = ft_strdup(old_path);
			break ;
		}
		head = head->next;
	}
	free(old_path);
}

void	handle_cd(char *path)
{
	char	*s;

	s = NULL;
	s = getcwd(s, 1024);
	if (ft_strmatch("..", path) && s == NULL)
	{
		ft_put_error("cd", "error retrieving current directory");
		ft_put_error("getcwd", "cannot access parent directories");
		s = ft_strjoin(ft_get_env("PWD"), "/");
		path = ft_strjoin(s, path);
		ft_update_pwd(path);
		free(s);
	}
	else
	{
		path = ft_get_pwd();
		ft_update_pwd(path);
		g_msh.exit_status = 0;
		free(s);
	}
}

void	ft_cd(char **cmd)
{
	char	*path;
	char	*old_path;

	old_path = ft_strdup(ft_get_env("PWD"));
	if (!*(cmd + 1) || ft_strmatch("~", *(cmd + 1)))
		path = ft_get_env("HOME");
	else
		path = *(cmd + 1);
	if (chdir(path))
	{
		ft_put_error(path, strerror(errno));
		g_msh.exit_status = 1;
		free(old_path);
	}
	else
	{
		handle_cd(path);
		ft_update_oldpwd(old_path);
	}
}

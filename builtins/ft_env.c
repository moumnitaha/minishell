/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoumni <tmoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 09:55:13 by tmoumni           #+#    #+#             */
/*   Updated: 2023/08/31 20:09:12 by tmoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

int	equal_index(char *str)
{
	int	index;

	index = 0;
	while (str[index])
	{
		if (str[index] == '=')
			return (index);
		index++;
	}
	return (0);
}

void	print_env(int p)
{
	t_env	*h;

	h = g_msh.env;
	while (h)
	{
		if (p)
		{
			printf("declare -x ");
			if (h->equal)
				printf("%s=\"%s\"\n", h->name, h->value);
			else
				printf("%s\n", h->name);
		}
		else
		{
			if (h->equal)
				printf("%s=%s\n", h->name, h->value);
		}
		h = h->next;
	}
}

void	init_empty_env(char **env)
{
	env[0] = "PWD=/Users/tmoumni/Desktop/minishell";
	env[1] = "SHLVL=1";
	env[2] = "_=/usr/bin/env";
	env[3] = NULL;
}

void	ft_env_init(char **env)
{
	int		index;
	char	*name;
	char	*value;
	int		shlvl;
	char	*s;

	if (!env || !env[0])
		init_empty_env(env);
	g_msh.env = NULL;
	while (*env)
	{
		index = equal_index(*env);
		name = ft_substr(*env, 0, index);
		value = ft_substr(*env, index + 1, ft_strlen(*env) - index);
		if (ft_strmatch(name, "SHLVL"))
		{
			shlvl = ft_atoi(value) + 1;
			free(value);
			s = ft_itoa(shlvl);
			value = ft_strdup(s);
			free(s);
		}
		ft_lstadd_back(&g_msh.env, ft_lstnew_env(name, value, true));
		env++;
	}
}

int	has_name(char *name)
{
	t_env	*head;

	head = g_msh.env;
	while (head)
	{
		if (ft_strmatch(head->name, name))
			return (1);
		head = head->next;
	}
	return (0);
}

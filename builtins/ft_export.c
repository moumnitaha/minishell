/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoumni <tmoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 16:37:48 by tmoumni           #+#    #+#             */
/*   Updated: 2023/08/31 19:54:07 by tmoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

int	valid_ide(char *str)
{
	int	i;

	i = 0;
	if (ft_isdigit((char)(str[0])))
		return (0);
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	ft_prt_err(char *name, char *value, char *cmd)
{
	if (!valid_ide(name) || !ft_strlen(cmd))
	{
		ft_put_error(cmd, " not a valid identifier");
		g_msh.exit_status = 1;
		free(name);
		free(value);
		return (1);
	}
	return (0);
}

int	fix_keys(char **name, char **value, char *cmd)
{
	int		index;
	char	*new;
	int		inc;

	index = equal_index(cmd);
	inc = 0;
	(void)value;
	if (!index)
	{
		*name = ft_strdup(cmd);
		*value = ft_strdup("");
	}
	else
	{
		*name = ft_substr(cmd, 0, index);
		if ((*name)[ft_strlen(*name) - 1] == '+')
		{
			new = ft_substr(*name, 0, ft_strlen(*name) - 1);
			free(*name);
			*name = new;
			inc = 1;
		}
		*value = ft_substr(cmd, index + 1, ft_strlen(cmd) - index);
	}
	return (inc);
}

void	handle_edit(char *cmd, char *name, char *value, int inc)
{
	if (equal_index(cmd))
		edit_node(&g_msh.env, name, value, inc);
	else
	{
		free(name);
		free(value);
	}
}

void	ft_export(char **cmd)
{
	char	*name;
	char	*value;
	int		inc;

	if (!(*(cmd + 1)))
		print_env(1);
	cmd++;
	inc = 0;
	g_msh.exit_status = 0;
	while (*cmd)
	{
		inc = fix_keys(&name, &value, *cmd);
		if (!ft_prt_err(name, value, *cmd))
		{
			if (has_name(name))
				handle_edit(*cmd, name, value, inc);
			else
				ft_lstadd_back(&g_msh.env, ft_lstnew_env(name, value,
						equal_index(*cmd)));
		}
		cmd++;
	}
}

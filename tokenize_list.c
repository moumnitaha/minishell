/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyassine <eyassine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 23:16:30 by eyassine          #+#    #+#             */
/*   Updated: 2023/08/28 16:11:57 by eyassine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

int	ft_strmatch(char *s0, char *s1)
{
	int	i;

	i = 0;
	if (!s0 || !s1)
		return (0);
	while (s1[i] && s0[i])
	{
		if (s0[i] != s1[i])
			return (0);
		i++;
	}
	if (s0[i] != '\0' || s1[i] != '\0')
		return (0);
	return (1);
}

void	cmd_fails(t_list *list, t_cmd *cmd)
{
	ft_free_list(list);
	ft_free_cmd(cmd);
	exit(1);
}

void	free_type(char **type, int i, t_list *list)
{
	if (!type[i])
	{
		ft_free_arr(type);
		ft_free_list(list);
		exit(1);
	}
}

char	**allocate_type(t_list *list)
{
	char	**type;

	type = malloc(sizeof(char *) * 7);
	if (!type)
	{
		ft_free_list(list);
		exit(1);
	}
	type[0] = ft_strdup("");
	free_type(type, 0, list);
	type[1] = ft_strdup("<<");
	free_type(type, 1, list);
	type[2] = ft_strdup("|");
	free_type(type, 2, list);
	type[3] = ft_strdup("<");
	free_type(type, 3, list);
	type[4] = ft_strdup(">>");
	free_type(type, 4, list);
	type[5] = ft_strdup(">");
	free_type(type, 5, list);
	type[6] = NULL;
	return (type);
}

int	tokenize_list(t_list *list)
{
	char	**type;
	int		i;

	type = allocate_type(list);
	while (list)
	{
		i = 1;
		while (i < 6 && list->tokens == 0 && type[i])
		{
			if (ft_strmatch(type[i], list->content) && !list->expand)
				list->tokens = i;
			i++;
		}
		if (list->tokens == 0)
		{
			if (list->content[0] == '-')
				list->tokens = OPTION;
			else
				list->tokens = WORD;
		}
		list = list->next;
	}
	ft_free_arr(type);
	return (1);
}

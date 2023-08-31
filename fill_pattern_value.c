/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_pattern_value.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyassine <eyassine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 16:42:36 by eyassine          #+#    #+#             */
/*   Updated: 2023/08/29 12:32:06 by eyassine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msh.h"

char	**allocate_value(char **pattern)
{
	char	**value;
	int		i;

	i = 0;
	while (pattern[i])
		i++;
	value = malloc(sizeof(char *) * (i + 1));
	if (!value)
		return (NULL);
	value[i] = NULL;
	return (value);
}

void	check_if_match(char *s, char *env, int *match, int *j)
{
	while (s[*j])
	{
		if (s[*j] != env[*j] && s[*j])
		{
			if (s[*j] == '=')
			{
				*j += 1;
				*match = 1;
			}
			break ;
		}
		*j += 1;
		if (s[*j] == '\0' && env[*j] == '=')
		{
			*j += 1;
			*match = 1;
		}
	}
}

char	*ft_match_path(char *s, char **env)
{
	int		i;
	int		j;
	int		match;
	char	*value;

	i = 0;
	match = 0;
	value = NULL;
	while (env[i])
	{
		j = 0;
		if (env[i][j] == *s)
		{
			check_if_match(s, env[i], &match, &j);
			if (match)
			{
				value = env[i] + j;
				match = 0;
			}
		}
		i++;
	}
	return (value);
}

char	**fill_pattern_value(char **pattern, char **env)
{
	char	**value;
	char	*env_content;
	int		i;

	i = 0;
	value = allocate_value(pattern);
	while (pattern[i])
	{
		if (ft_strmatch(pattern[i], "$") || ft_strmatch(pattern[i], "$=")
			|| ft_strmatch(pattern[i], "$?"))
			value[i] = pattern[i];
		else
		{
			env_content = ft_match_path(pattern[i], env);
			if (env_content)
				value[i] = env_content;
			else
				value[i] = "\0";
		}
		i++;
	}
	return (value);
}

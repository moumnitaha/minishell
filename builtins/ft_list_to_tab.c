/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_to_tab.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoumni <tmoumni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 12:18:58 by tmoumni           #+#    #+#             */
/*   Updated: 2023/08/29 10:47:09 by tmoumni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../msh.h"

int	list_size(t_env *head)
{
	int		count;
	t_env	*current;

	count = 0;
	current = head;
	while (current != NULL)
	{
		count++;
		current = current->next;
	}
	return (count);
}

char	**ft_list_to_tab(t_env *head)
{
	char	**env;
	int		i;
	int		count;
	char	*str;
	char	*str2;

	count = list_size(head);
	env = (char **)malloc((count + 1) * sizeof(char *));
	if (!env)
		return (NULL);
	i = 0;
	while (head)
	{
		str = ft_strjoin(head->name, "=");
		str2 = ft_strjoin(str, head->value);
		env[i] = ft_strdup(str2);
		free(str);
		free(str2);
		head = head->next;
		i++;
	}
	env[count] = NULL;
	return (env);
}

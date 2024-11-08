/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olardeux <olardeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 06:37:44 by olardeux          #+#    #+#             */
/*   Updated: 2024/10/31 07:33:12 by olardeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	name_match(char *name, char *arg)
{
	int	i;

	i = 0;
	while (name[i] && arg[i])
	{
		if (name[i] != arg[i])
			return (0);
		i++;
	}
	if (!name[i] && !arg[i])
		return (1);
	return (0);
}

void	unset_var(t_env *prev, t_env *tmp, t_env **env)
{
	if (tmp == *env)
		*env = tmp->next;
	else
		prev->next = tmp->next;
	free(tmp->name);
	free(tmp->value);
	free(tmp);
	tmp = prev;
}

int	ft_unset(t_cmd_list *cmd, t_env *env)
{
	t_env	*tmp;
	t_env	*prev;
	int		i;

	i = 1;
	while (cmd->args[i])
	{
		tmp = env;
		prev = env;
		while (tmp)
		{
			if (name_match(tmp->name, cmd->args[i]))
				unset_var(prev, tmp, &env);
			prev = tmp;
			tmp = tmp->next;
		}
		i++;
	}
	return (0);
}

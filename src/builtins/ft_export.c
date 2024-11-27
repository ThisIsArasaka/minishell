/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olardeux <olardeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 06:30:13 by olardeux          #+#    #+#             */
/*   Updated: 2024/11/27 09:02:45 by olardeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sort_env(t_env *env)
{
	t_env	*tmp;
	t_env	*tmp2;
	char	*name;
	char	*value;

	tmp = env;
	while (tmp)
	{
		tmp2 = tmp->next;
		while (tmp2)
		{
			if (ft_strncmp(tmp->name, tmp2->name, ft_strlen(tmp->name)) > 0)
			{
				name = tmp->name;
				value = tmp->value;
				tmp->name = tmp2->name;
				tmp->value = tmp2->value;
				tmp2->name = name;
				tmp2->value = value;
			}
			tmp2 = tmp2->next;
		}
		tmp = tmp->next;
	}
}

void	print_env_export(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		printf("export %s=%s\n", tmp->name, tmp->value);
		tmp = tmp->next;
	}
}

int	isvalid(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	add_env(t_env **env, char *arg)
{
	t_env	*new;
	t_env	*tmp;

	new = param_env(arg);
	if (!new)
		return (0);
	tmp = *env;
	while (tmp && tmp->next)
	{
		if (name_match(tmp->name, new->name) && tmp->value[0])
		{
			free(tmp->value);
			tmp->value = new->value;
			free(new->name);
			free(new);
			return (1);
		}
		tmp = tmp->next;
	}
	new->next = NULL;
	if (!*env)
		return (*env = new, 1);
	tmp->next = new;
	return (1);
}

int	ft_export(t_cmd_list *cmd, t_env **env)
{
	int	i;

	i = 1;
	sort_env(*env);
	while (cmd->args[i])
	{
		if (cmd->args[i][0])
		{
			if (!isvalid(cmd->args[i]))
				error_msg("export", cmd->args[i]);
			else
			{
				if (!add_env(env, cmd->args[i]))
					return (0);
			}
		}
		i++;
	}
	if (i == 1)
		print_env_export(*env);
	sort_env(*env);
	return (1);
}

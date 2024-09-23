/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olardeux <olardeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 03:22:11 by olardeux          #+#    #+#             */
/*   Updated: 2024/09/22 09:12:02 by olardeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*param_env(char *env)
{
	t_env	*new_env;
	int		i;

	i = 0;
	new_env = malloc(sizeof(t_env));
	if (!new_env)
		return (NULL);
	while (env[i] && env[i] != '=')
		i++;
	new_env->name = ft_substr(env, 0, i);
	if (!new_env->name)
		return (free(new_env), NULL);
	new_env->value = ft_strdup(env + i + 1);
	if (!new_env->value)
		return (free(new_env->name), free(new_env), NULL);
	return (new_env);
}

char	*get_env_value(t_env *env, char *name)
{
	int	i;

	i = 0;
	while (name[i] && name[i] != '=')
		i++;
	while (env)
	{
		if (!ft_strncmp(env->name, name, i))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

t_env	*init_env(char **envp)
{
	t_env	*env;
	t_env	*tmp;
	int		i;

	i = 0;
	env = param_env(envp[i]);
	if (!env)
		return (NULL);
	tmp = env;
	i++;
	while (envp[i])
	{
		tmp->next = param_env(envp[i]);
		if (!tmp->next)
			return (free_env(env), NULL);
		tmp = tmp->next;
		i++;
	}
	tmp->next = NULL;
	return (env);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olardeux <olardeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 10:56:33 by olardeux          #+#    #+#             */
/*   Updated: 2024/11/09 22:19:29 by olardeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	add_to_array(char **array, t_env *env, int i)
{
	array[i] = ft_strjoin(env->name, "=");
	if (!array[i])
		return (free_tab(array), 0);
	array[i] = ft_strjoin_free(array[i], env->value);
	if (!array[i])
		return (free_tab(array), 0);
	return (1);
}

char	**env_to_array(t_env *env)
{
	int		i;
	char	**array;
	t_env	*tmp;

	i = 0;
	tmp = env;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	array = malloc(sizeof(char *) * (i + 1));
	if (!array)
		return (NULL);
	i = 0;
	tmp = env;
	while (tmp)
	{
		if (!add_to_array(array, tmp, i))
			return (error_msg(MALLOC_ERROR, NULL), NULL);
		tmp = tmp->next;
		i++;
	}
	array[i] = NULL;
	return (array);
}

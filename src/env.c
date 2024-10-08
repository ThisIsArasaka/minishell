/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olardeux <olardeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 03:22:11 by olardeux          #+#    #+#             */
/*   Updated: 2024/10/07 05:30:18 by olardeux         ###   ########.fr       */
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
	int		i;
	t_env	*tmp;

	i = 0;
	tmp = env;
	while (name[i] && !ft_isblank(name[i]) && !is_special_char(name[i])
		&& name[i] != '"' && name[i] != '\\' && name[i] != '$' && name[i] != '='
		&& name[i] != '/')
		i++;
	while (tmp)
	{
		if (!ft_strncmp(tmp->name, name, i) && !tmp->name[i])
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

char	*get_env_exec(t_env *env, char *name)
{
	int		i;
	char	**path;
	char	*cmd;

	i = 0;
	if (name[0] == '.' || name[0] == '/')
		return (ft_strdup(name));
	path = ft_split(get_env_value(env, "PATH"), ':');
	if (!path)
		return (NULL);
	while (path[i++])
	{
		path[i] = ft_strjoin(path[i], "/");
		if (!path[i])
			return (free_tokens(path), NULL);
		path[i] = ft_strjoin(path[i], name);
		if (!path[i])
			return (free_tokens(path), NULL);
		if (!access(path[i], F_OK))
		{
			cmd = ft_strdup(path[i]);
			return (free_tokens(path), cmd);
		}
	}
	return (free_tokens(path), NULL);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olardeux <olardeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 03:22:11 by olardeux          #+#    #+#             */
/*   Updated: 2024/12/02 11:44:24 by olardeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*param_env(char *env)
{
	t_env	*new_env;
	int		i;

	i = 0;
	new_env = malloc(sizeof(t_env));
	if (!new_env || !env)
		return (NULL);
	while (env[i] && env[i] != '=')
		i++;
	new_env->name = ft_substr(env, 0, i);
	if (!new_env->name)
		return (free(new_env), NULL);
	if (env[i] == '=')
	{
		new_env->value = ft_strdup(env + i + 1);
		if (!new_env->value)
			return (free(new_env->name), free(new_env), NULL);
	}
	else
		new_env->value = ft_strdup("");
	return (new_env);
}

char	*get_env_value(t_env *env, char *name)
{
	int		i;
	t_env	*tmp;

	i = 0;
	tmp = env;
	while (name[i] && !ft_isblank(name[i]) && !is_special_char(name[i])
		&& name[i] != '"' && name[i] != '\\'
		&& name[i] != '$' && name[i] != '='
		&& name[i] != '/' && name[i] != '.' && name[i] != '\''
		&& !is_special_char(name[i]))
		i++;
	while (tmp)
	{
		if (!ft_strncmp(tmp->name, name, i) && !tmp->name[i])
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

char	*add_cmd_path(char *path, char *cmd)
{
	path = ft_strjoin_free(path, "/");
	if (!path)
		return (NULL);
	path = ft_strjoin_free(path, cmd);
	if (!path)
		return (NULL);
	return (path);
}

char	*get_env_exec(t_env *env, char *name)
{
	int		i;
	char	**path;
	char	*cmd;
	char	*path_var;

	i = -1;
	if (name[0] == '.' || name[0] == '/' || name[0] == '\0')
		return (name);
	path_var = get_env_value(env, "PATH");
	if (!path_var)
		return (name);
	path = ft_split(path_var, ':');
	if (!path)
		return (NULL);
	while (path[++i])
	{
		path[i] = add_cmd_path(path[i], name);
		if (!access(path[i], F_OK))
		{
			cmd = ft_strdup(path[i]);
			return (free_tab(path), free(name), cmd);
		}
	}
	return (free_tab(path), name);
}

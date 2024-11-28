/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olardeux <olardeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 22:12:38 by olardeux          #+#    #+#             */
/*   Updated: 2024/11/28 23:55:10 by olardeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*set_path(t_cmd_list *cmd, t_env *env)
{
	char	*path;

	if (!cmd->args[1])
	{
		path = get_env_value(env, "HOME");
		if (!path)
			return (error_msg(HOME_NOT_SET, NULL), NULL);
	}
	else if (cmd->args[1][0] == '~')
	{
		path = ft_strjoin(get_env_value(env, "HOME"), cmd->args[1] + 1);
		if (!path)
			return (error_msg(MALLOC_ERROR, NULL), NULL);
	}
	else
		path = ft_strdup(cmd->args[1]);
	if (!path)
		return (error_msg(MALLOC_ERROR, NULL), NULL);
	return (path);
}

void	update_pwd(t_env *env)
{
	char	*pwd;
	char	*oldpwd;
	t_env	*tmp;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (error_msg(CD_ERROR, NULL));
	oldpwd = get_env_value(env, "PWD");
	tmp = env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->name, "PWD", 4))
		{
			free(tmp->value);
			tmp->value = pwd;
		}
		if (!ft_strncmp(tmp->name, "OLDPWD", 7))
		{
			free(tmp->value);
			tmp->value = oldpwd;
		}
		tmp = tmp->next;
	}
}

int	ft_cd(t_cmd_list *cmd, t_data *data)
{
	char	*path;

	if (cmd->args[2])
		return (data->excode = 1, error_msg("cd", "too many arguments"), 1);
	path = set_path(cmd, data->env);
	if (!path)
		return (1);
	if (chdir(path) == -1)
	{
		free(path);
		data->excode = 1;
		return (error_msg(CD_ERROR, NULL), 1);
	}
	update_pwd(data->env);
	free(path);
	return (0);
}

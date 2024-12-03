/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olardeux <olardeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 22:12:38 by olardeux          #+#    #+#             */
/*   Updated: 2024/12/03 03:48:53 by olardeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*set_path(t_cmd_list *cmd, t_env *env)
{
	char	*path;

	if (!cmd->args[1] || cmd->args[1][0] == '~')
	{
		path = get_env_value(env, "HOME");
		if (!path)
			return (error_msg(HOME_NOT_SET, NULL), NULL);
		if (!cmd->args[1])
			path = ft_strdup(path);
		else
			path = ft_strjoin(path, cmd->args[1] + 1);
	}
	else if (cmd->args[1][0] == '-')
	{
		path = get_env_value(env, "OLDPWD");
		if (!path)
			return (error_msg("cd", "OLDPWD not set"), NULL);
		path = ft_strdup(path);
		printf("%s\n", path);
	}
	else
		path = ft_strdup(cmd->args[1]);
	if (!path)
		return (error_msg(MALLOC_ERROR, NULL), NULL);
	return (path);
}

t_env	*create_pwd(t_env *env)
{
	t_env	*new_oldpwd;
	t_env	*new_pwd;

	new_oldpwd = malloc(sizeof(t_env));
	if (!new_oldpwd)
		return (error_msg(MALLOC_ERROR, NULL), NULL);
	new_pwd = malloc(sizeof(t_env));
	if (!new_pwd)
		return (error_msg(MALLOC_ERROR, NULL), NULL);
	new_oldpwd->name = ft_strdup("OLDPWD");
	new_oldpwd->value = getcwd(NULL, 0);
	new_pwd->name = ft_strdup("PWD");
	new_pwd->value = getcwd(NULL, 0);
	new_oldpwd->next = new_pwd;
	new_pwd->next = env;
	return (new_oldpwd);
}

void	update_pwd(t_env *env)
{
	char	*pwd;
	char	*oldpwd;
	t_env	*tmp;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (error_msg(CD_ERROR, NULL));
	oldpwd = ft_strdup(get_env_value(env, "PWD"));
	tmp = env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->name, "PWD", 4))
		{
			free(tmp->value);
			tmp->value = ft_strdup(pwd);
		}
		if (!ft_strncmp(tmp->name, "OLDPWD", 7))
		{
			free(tmp->value);
			tmp->value = ft_strdup(oldpwd);
		}
		tmp = tmp->next;
	}
	free(pwd);
	free(oldpwd);
}

int	ft_cd(t_cmd_list *cmd, t_data *data)
{
	char	*path;

	if (cmd->args[1] && cmd->args[2])
		return (data->excode = 1, error_msg("cd", "too many arguments"), 1);
	if (!data->env)
		data->env = create_pwd(data->env);
	path = set_path(cmd, data->env);
	if (!path)
		return (data->excode = 1, 1);
	if (chdir(path) == -1)
	{
		free(path);
		data->excode = 1;
		return (perror(CD_ERROR), 1);
	}
	update_pwd(data->env);
	free(path);
	return (0);
}

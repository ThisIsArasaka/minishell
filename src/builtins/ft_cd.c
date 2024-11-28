/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olardeux <olardeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 22:12:38 by olardeux          #+#    #+#             */
/*   Updated: 2024/11/27 06:31:55 by olardeux         ###   ########.fr       */
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

int	ft_cd(t_cmd_list *cmd, t_env *env)
{
	char	*path;

	if (cmd->args[2])
		return (error_msg("cd", "too many arguments"), 1);
	path = set_path(cmd, env);
	if (!path)
		return (1);
	if (chdir(path) == -1)
	{
		free(path);
		return (error_msg(CD_ERROR, NULL), 1);
	}
	free(path);
	return (0);
}

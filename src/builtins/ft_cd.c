/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olardeux <olardeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 22:12:38 by olardeux          #+#    #+#             */
/*   Updated: 2024/10/31 07:12:13 by olardeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(t_cmd_list *cmd, t_env *env)
{
	char	*path;

	if (!cmd->args[1])
	{
		path = get_env_value(env, "HOME");
		if (!path)
			return (error_msg(HOME_NOT_SET, NULL), 1);
	}
	else if (cmd->args[1][0] == '~')
	{
		path = ft_strjoin(get_env_value(env, "HOME"), cmd->args[1] + 1);
		if (!path)
			return (error_msg(MALLOC_ERROR, NULL), 1);
	}
	else
		path = ft_strdup(cmd->args[1]);
	if (!path)
		return (error_msg(MALLOC_ERROR, NULL), 1);
	if (chdir(path) == -1)
	{
		free(path);
		return (error_msg(CD_ERROR, NULL), 1);
	}
	free(path);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olardeux <olardeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 08:05:54 by olardeux          #+#    #+#             */
/*   Updated: 2024/10/29 22:18:53 by olardeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin(t_data *data)
{
	if (!ft_strncmp(data->cmd_list->cmd, "echo\0", 5))
		return (ft_echo(data->cmd_list));
	// else if (!ft_strncmp(cmd->cmd, "env\0", 4))
	// 	return (ft_env(env));
	else if (!ft_strncmp(data->cmd_list->cmd, "export\0", 7))
		return (ft_export(data->cmd_list, data->env));
	else if (!ft_strncmp(data->cmd_list->cmd, "unset\0", 6))
		return (ft_unset(data->cmd_list, data->env));
	else if (!ft_strncmp(data->cmd_list->cmd, "cd\0", 3))
		return (ft_cd(data->cmd_list, data->env));
	else if (!ft_strncmp(data->cmd_list->cmd, "pwd\0", 4))
		return (ft_pwd());
	else if (!ft_strncmp(data->cmd_list->cmd, "exit\0", 5))
		return (ft_exit(data));
	return (0);
}

int	is_builtin(t_cmd_list *cmd)
{
	if (!ft_strncmp(cmd->cmd, "echo\0", 5))
		return (1);
	else if (!ft_strncmp(cmd->cmd, "env\0", 4))
		return (1);
	else if (!ft_strncmp(cmd->cmd, "export\0", 7))
		return (1);
	else if (!ft_strncmp(cmd->cmd, "unset\0", 6))
		return (1);
	else if (!ft_strncmp(cmd->cmd, "cd\0", 3))
		return (1);
	else if (!ft_strncmp(cmd->cmd, "pwd\0", 4))
		return (1);
	else if (!ft_strncmp(cmd->cmd, "exit\0", 5))
		return (1);
	return (0);
}

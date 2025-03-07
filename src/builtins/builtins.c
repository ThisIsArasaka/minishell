/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marida-c <marida-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 08:05:54 by olardeux          #+#    #+#             */
/*   Updated: 2024/12/02 15:46:53 by marida-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin(t_data *data, t_cmd_list *cmd)
{
	if (!ft_strncmp(cmd->cmd, "echo\0", 5))
		return (ft_echo(cmd));
	else if (!ft_strncmp(cmd->cmd, "env\0", 4))
		return (ft_env(data->env));
	else if (!ft_strncmp(cmd->cmd, "export\0", 7))
		return (ft_export(cmd, data));
	else if (!ft_strncmp(cmd->cmd, "unset\0", 6))
		return (ft_unset(cmd, &data->env));
	else if (!ft_strncmp(cmd->cmd, "cd\0", 3))
		return (ft_cd(cmd, data));
	else if (!ft_strncmp(cmd->cmd, "pwd\0", 4))
		return (ft_pwd(data, cmd));
	else if (!ft_strncmp(cmd->cmd, "exit\0", 5))
		return (ft_exit(data, cmd));
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marida-c <marida-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 04:15:03 by olardeux          #+#    #+#             */
/*   Updated: 2024/12/02 14:22:06 by marida-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(t_cmd_list *cmd)
{
	int	i;
	int	new_line;
	int	j;

	i = 1;
	new_line = 1;
	j = 2;
	while (cmd->args[i] && cmd->args[i][0] == '-' &&
			ft_strncmp(cmd->args[i], "-n", 2) == 0)
	{
		while (cmd->args[i][j] == 'n')
			j++;
		if (cmd->args[i][j] == '\0')
			new_line = 0;
		else
			break ;
		i++;
	}
	while (cmd->args[i])
	{
		ft_putstr_fd(cmd->args[i], 1);
		if (cmd->args[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (new_line)
		ft_putstr_fd("\n", 1);
	return (0);
}

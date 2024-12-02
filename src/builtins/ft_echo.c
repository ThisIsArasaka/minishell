/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marida-c <marida-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 04:15:03 by olardeux          #+#    #+#             */
/*   Updated: 2024/12/02 15:08:06 by marida-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	nl_init(char **args, int *i)
{
	int	j;
	int	res;

	j = 1;
	res = 1;
	while (args[*i] && args[*i][0] == '-' &&
			ft_strncmp(args[*i], "-n", 2) == 0)
	{
		while (args[*i][j] == 'n')
			j++;
		if (args[*i][j] == '\0')
			res = 0;
		else
			break ;
		(*i)++;
	}
	return (res);
}

int	ft_echo(t_cmd_list *cmd)
{
	int	i;
	int	new_line;

	i = 1;
	new_line = nl_init(cmd->args, &i);
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

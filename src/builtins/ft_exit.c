/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olardeux <olardeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 07:47:08 by olardeux          #+#    #+#             */
/*   Updated: 2024/11/29 10:02:34 by olardeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	atoi_check(char *str)
{
	int		i;
	long	res;

	i = 0;
	res = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		res = res * 10 + str[i] - '0';
		if (res > INT_MAX)
			return (0);
		i++;
	}
	return (1);
}

int	ft_exit(t_data *data, t_cmd_list *cmd)
{
	if (cmd->args[1])
	{
		if (cmd->args[2])
			return (error_msg("exit", "too many arguments"), data->excode = 1,
				1);
		if (!atoi_check(cmd->args[1]))
		{
			error_msg("exit", "numeric argument required");
			data->excode = 2;
		}
		else
			data->excode = ft_atoi(cmd->args[1]);
	}
	free_cmd_list(data->cmd_list);
	free_env(data->env);
	free(data->line);
	exit(data->excode);
}

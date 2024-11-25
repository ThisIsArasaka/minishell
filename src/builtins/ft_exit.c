/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olardeux <olardeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 07:47:08 by olardeux          #+#    #+#             */
/*   Updated: 2024/11/25 06:24:26 by olardeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	atoi_check(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_exit(t_data *data)
{
	int	exit_status;

	exit_status = 0;
	if (data->cmd_list->args[1])
	{
		if (data->cmd_list->args[2])
			return (error_msg("exit", "too many arguments"), 1);
		if (!atoi_check(data->cmd_list->args[1]))
		{
			error_msg("exit", "numeric argument required");
			exit_status = 255;
		}
		else
			exit_status = ft_atoi(data->cmd_list->args[1]);
	}
	free_cmd_list(data->cmd_list);
	free_env(data->env);
	free(data->line);
	exit(exit_status);
}

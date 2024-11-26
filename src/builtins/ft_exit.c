/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrn <mrn@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 07:47:08 by olardeux          #+#    #+#             */
/*   Updated: 2024/11/21 15:35:30 by mrn              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(t_data *data)
{
	printf(PURPLE"executing exit...\n"RESET);
	free_cmd_list(data->cmd_list);
	free_env(data->env);
	free(data->line);
	exit(0);
}

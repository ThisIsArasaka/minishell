/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olardeux <olardeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 09:09:59 by olardeux          #+#    #+#             */
/*   Updated: 2024/11/27 09:10:57 by olardeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_free(t_data *data)
{
	free_cmd_list(data->cmd_list);
	free(data->line);
	free_env(data->env);
	exit(data->excode);
}
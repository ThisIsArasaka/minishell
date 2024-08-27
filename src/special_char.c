/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_char.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olardeux <olardeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 14:49:07 by olardeux          #+#    #+#             */
/*   Updated: 2024/08/26 07:27:21 by olardeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirect_input(t_cmd_list *cmd, char **tokens, int start, int arg_num)
{
	if (tokens[start + 1])
	{
		cmd->args[arg_num] = read_file(tokens[start + 1]);
		if (!cmd->args[arg_num])
			return (0);
	}
	else
		return (0);
	return (1);
}

int	redirect_output(t_cmd_list *cmd, char **tokens, int start)
{
	if (tokens[start + 1])
	{
		cmd->output = ft_strdup(tokens[start + 1]);
		if (!cmd->output)
			return (0);
	}
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_char.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olardeux <olardeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 14:49:07 by olardeux          #+#    #+#             */
/*   Updated: 2024/09/10 11:59:39 by olardeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirect_input(t_cmd_list *cmd, t_parsing *parsing, int start, int arg_num)
{
	cmd->args[arg_num] = read_file(parsing->tokens[start + 1]);
	if (!cmd->args[arg_num])
		return (0);
	parsing->i += 2;
	return (1);
}

int	redirect_output(t_cmd_list *cmd, t_parsing *parsing, int start)
{
	cmd->output = ft_strdup(parsing->tokens[start + 1]);
	if (!cmd->output)
		return (0);
	parsing->i += 2;
	return (1);
}

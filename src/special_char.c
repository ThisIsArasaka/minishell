/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_char.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olardeux <olardeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 14:49:07 by olardeux          #+#    #+#             */
/*   Updated: 2024/10/28 00:02:04 by olardeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirect_input(t_cmd_list *cmd, t_parsing *parsing, int start, int arg_num)
{
	if (!parsing->tokens[start + 1])
		return (error_msg(SYNTAX_ERROR, NULL), 0);
	if (cmd->input)
		free(cmd->input);
	cmd->input = read_file(parsing->tokens[start + 1]);
	if (!cmd->args[arg_num])
		return (0);
	parsing->i += 2;
	return (1);
}

int	redirect_output(t_cmd_list *cmd, t_parsing *parsing, int start)
{
	if (!parsing->tokens[start + 1])
		return (error_msg(SYNTAX_ERROR, NULL), 0);
	cmd->output = ft_strdup(parsing->tokens[start + 1]);
	if (!cmd->output)
		return (error_msg(MALLOC_ERROR, NULL), 0);
	parsing->i += 2;
	return (1);
}

int	redirect_append(t_cmd_list *cmd, t_parsing *parsing, int start)
{
	if (!parsing->tokens[start + 1])
		return (error_msg(SYNTAX_ERROR, NULL), 0);
	cmd->output = ft_strdup(parsing->tokens[start + 1]);
	if (!cmd->output)
		return (error_msg(MALLOC_ERROR, NULL), 0);
	cmd->append = 1;
	parsing->i += 2;
	return (1);
}

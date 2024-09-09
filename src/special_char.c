/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_char.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olardeux <olardeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 14:49:07 by olardeux          #+#    #+#             */
/*   Updated: 2024/09/03 13:43:48 by olardeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirect_input(t_cmd_list *cmd, t_parsing *parsing, int start, int arg_num)
{
	if (parsing->tokens[start + 1] && !quote_in_token(parsing->tokens[start
			+ 1]))
	{
		cmd->args[arg_num] = read_file(parsing->tokens[start + 1]);
		if (!cmd->args[arg_num])
			return (0);
		parsing->i += 2;
	}
	else if (parsing->tokens[start + 1] && quote_in_token(parsing->tokens[start
			+ 1]))
	{
		printf("quote[%d] = %s\n", parsing->quote_count,
			parsing->quote[parsing->quote_count]);
		cmd->args[arg_num] = read_file(parsing->quote[parsing->quote_count]);
		if (!cmd->args[arg_num])
			return (0);
		parsing->quote_count++;
		parsing->i += quote_span(parsing->tokens + start,
				parsing->tokens[start][0]);
	}
	else
		return (0);
	return (1);
}

int	redirect_output(t_cmd_list *cmd, t_parsing *parsing, int start)
{
	if (parsing->tokens[start + 1] && !quote_in_token(parsing->tokens[start
			+ 1]))
	{
		cmd->output = ft_strdup(parsing->tokens[start + 1]);
		if (!cmd->output)
			return (0);
		parsing->i += 2;
	}
	else if (parsing->tokens[start + 1] && quote_in_token(parsing->tokens[start
			+ 1]))
	{
		cmd->output = ft_strdup(parsing->quote[parsing->quote_count]);
		if (!cmd->output)
			return (0);
		parsing->quote_count++;
		parsing->i += quote_span(parsing->tokens + start,
				parsing->tokens[start][0]);
	}
	return (1);
}

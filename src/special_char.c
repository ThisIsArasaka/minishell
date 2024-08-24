/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_char.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olardeux <olardeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 14:49:07 by olardeux          #+#    #+#             */
/*   Updated: 2024/08/24 15:38:20 by olardeux         ###   ########.fr       */
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

int	inquote_parsing(t_cmd_list *cmd, char **tokens, int start, int arg_num)
{
	int	i;

	i = 0;
	if (tokens[start][0] == '"')
		tokens[start]++;
	while (tokens[start + i] && last_char(tokens[start + i]) != '"')
	{
		cmd->args[arg_num] = ft_strjoin(cmd->args[arg_num], tokens[start + i]);
		if (!cmd->args[arg_num])
			return (0);
		cmd->args[arg_num] = ft_strjoin(cmd->args[arg_num], " ");
		if (!cmd->args[arg_num])
			return (0);
		i++;
	}
	tokens[start + i][ft_strlen(tokens[start + i]) - 1] = '\0';
	cmd->args[arg_num] = ft_strjoin(cmd->args[arg_num], tokens[start + i]);
	if (!cmd->args[arg_num])
		return (0);
	return (1);
}

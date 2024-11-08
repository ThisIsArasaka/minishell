/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_char.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olardeux <olardeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 14:49:07 by olardeux          #+#    #+#             */
/*   Updated: 2024/11/08 23:51:42 by olardeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirect_input(t_cmd_list *cmd, t_parsing *parsing, t_token **start)
{
	if (!(*start)->next)
		return (error_msg(SYNTAX_ERROR, NULL), 0);
	if (cmd->input)
		free(cmd->input);
	cmd->input = ft_strdup((*start)->next->token);
	parsing->i += 2;
	(*start) = (*start)->next->next;
	return (1);
}

int	redirect_append(t_cmd_list *cmd, t_parsing *parsing, t_token **start)
{
	if (!(*start)->next)
		return (error_msg(SYNTAX_ERROR, NULL), 0);
	cmd->output = ft_strdup((*start)->next->token);
	if (!cmd->output)
		return (error_msg(MALLOC_ERROR, NULL), 0);
	cmd->append = 1;
	parsing->i += 2;
	(*start) = (*start)->next->next;
	return (1);
}

int	redirect_output(t_cmd_list *cmd, t_parsing *parsing, t_token **start)
{
	if (!(*start)->next)
		return (error_msg(SYNTAX_ERROR, NULL), 0);
	if ((*start)->token[1] == '>')
	{
		if (!redirect_append(cmd, parsing, start))
			return (0);
	}
	else
	{
		cmd->output = ft_strdup((*start)->next->token);
		if (!cmd->output)
			return (error_msg(MALLOC_ERROR, NULL), 0);
		parsing->i += 2;
		(*start) = (*start)->next->next;
	}
	return (1);
}

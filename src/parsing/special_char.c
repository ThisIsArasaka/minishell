/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_char.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olardeux <olardeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 14:49:07 by olardeux          #+#    #+#             */
/*   Updated: 2024/11/20 10:52:25 by olardeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redir	*init_redir(void)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->file = NULL;
	redir->fd = -1;
	redir->type = -1;
	redir->next = NULL;
	return (redir);
}

int	redirect_heredoc(t_cmd_list *cmd, t_parsing *parsing, t_token **start)
{
	t_redir	*redir;

	redir = init_redir();
	if (!redir)
		return (error_msg(MALLOC_ERROR, NULL), 0);
	if (!set_redir(redir, cmd, *start))
		return (0);
	parsing->i += 2;
	(*start) = (*start)->next->next;
	return (1);
}

int	redirect_input(t_cmd_list *cmd, t_parsing *parsing, t_token **start)
{
	t_redir	*redir;

	if (!(*start)->next || (*start)->next->type != WORD)
		return (error_msg(SYNTAX_ERROR, NULL), 0);
	if ((*start)->token[1] == '<')
	{
		if (!redirect_heredoc(cmd, parsing, start))
			return (0);
	}
	else
	{
		redir = init_redir();
		if (!set_redir(redir, cmd, *start))
			return (0);
		parsing->i += 2;
		(*start) = (*start)->next->next;
	}
	return (1);
}

int	redirect_append(t_cmd_list *cmd, t_parsing *parsing, t_token **start)
{
	t_redir	*redir;

	redir = init_redir();
	if (!(*start)->next || (*start)->next->type != WORD)
		return (error_msg(SYNTAX_ERROR, NULL), 0);
	if (!set_redir(redir, cmd, *start))
		return (0);
	parsing->i += 2;
	(*start) = (*start)->next->next;
	return (1);
}

int	redirect_output(t_cmd_list *cmd, t_parsing *parsing, t_token **start)
{
	t_redir	*redir;

	if (!(*start)->next || (*start)->next->type != WORD)
		return (error_msg(SYNTAX_ERROR, NULL), 0);
	if ((*start)->token[1] == '>')
	{
		if (!redirect_append(cmd, parsing, start))
			return (0);
	}
	else
	{
		redir = init_redir();
		if (!set_redir(redir, cmd, *start))
			return (0);
		parsing->i += 2;
		(*start) = (*start)->next->next;
	}
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marida-c <marida-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 12:30:01 by marida-c          #+#    #+#             */
/*   Updated: 2024/12/02 12:30:03 by marida-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_input_redir(t_redir *redir, int fd_in, t_data *data)
{
	if (fd_in != -2)
		close(fd_in);
	if (redir->type == INPUT)
	{
		fd_in = open(redir->file, O_RDONLY);
		if (fd_in == -1)
		{
			perror(redir->file);
			data->excode = 1;
			return (-1);
		}
	}
	else if (redir->type == HEREDOC)
	{
		fd_in = handle_heredoc(redir->file, data);
		if (fd_in == -1)
		{
			perror("heredoc.tmp");
			return (-1);
		}
	}
	return (fd_in);
}

int	handle_output_redir(t_redir *redir, int fd_out, t_data *data)
{
	if (fd_out != -2)
		close(fd_out);
	if (redir->type == OUTPUT)
	{
		fd_out = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd_out == -1)
		{
			perror(redir->file);
			data->excode = 1;
			return (-1);
		}
	}
	else if (redir->type == APPEND)
	{
		fd_out = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd_out == -1)
		{
			perror(redir->file);
			data->excode = 1;
			return (-1);
		}
	}
	return (fd_out);
}

void	apply_redirections(t_cmd_list *cmd, int *fd_in, int *fd_out,
t_data *data)
{
	t_redir	*redir;

	redir = cmd->redir;
	while (redir)
	{
		if (redir->type == INPUT || redir->type == HEREDOC)
		{
			*fd_in = handle_input_redir(redir, *fd_in, data);
		}
		else if (redir->type == OUTPUT || redir->type == APPEND)
		{
			*fd_out = handle_output_redir(redir, *fd_out, data);
		}
		if (*fd_in == -1 || *fd_out == -1)
			break ;
		redir = redir->next;
	}
}

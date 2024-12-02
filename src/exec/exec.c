/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marida-c <marida-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 12:29:47 by marida-c          #+#    #+#             */
/*   Updated: 2024/12/02 12:29:49 by marida-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_fds_and_redirections(t_cmd_list *current_cmd, t_fd *fds,
		t_data *data)
{
	init_fds(fds);
	if (current_cmd->next)
	{
		if (pipe(fds->pipes) == -1)
		{
			data->excode = 1;
			error_msg("pipe failed", NULL);
			exit_free(data);
		}
	}
	apply_redirections(current_cmd, &fds->redir[0], &fds->redir[1], data);
	set_fds(fds);
}

void	execute_process(t_data *data, t_cmd_list *current_cmd, t_fd *fds)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		close_all_fds(fds);
		exit_free(data);
	}
	else if (pid == 0)
	{
		if (is_builtin(current_cmd))
			exec_bultin(data, fds, current_cmd);
		else
			execute_child(data, current_cmd, fds);
	}
}

void	exec_bultin(t_data *data, t_fd *fds, t_cmd_list *cmd)
{
	if (fds->pipes[0] != -2)
		close(fds->pipes[0]);
	if (fds->input != -2)
		close(fds->input);
	if (fds->output != -2)
		if (dup2(fds->output, STDOUT_FILENO) == -1)
			(close_all_fds(fds), exit(1));
	builtin(data, cmd);
	close_all_fds(fds);
	data->excode = 0;
	exit_free(data);
}

void	execute_child(t_data *data, t_cmd_list *cmd, t_fd *fds)
{
	if (fds->pipes[0] != -2)
		close(fds->pipes[0]);
	if (fds->input != -2)
		if (dup2(fds->input, STDIN_FILENO) == -1)
			(close_all_fds(fds), exit_free(data));
	if (fds->output != -2)
		if (dup2(fds->output, STDOUT_FILENO) == -1)
			(close_all_fds(fds), exit_free(data));
	close_all_fds(fds);
	exec_cmd(data, cmd, NULL);
}

// Fonction principale d'exécution des commandes
void	exec(t_data *data)
{
	t_cmd_list	*current_cmd;
	t_fd		fds;

	fds.input = -2;
	current_cmd = data->cmd_list;
	current_cmd->prev = NULL;
	while (current_cmd)
	{
		init_fds_and_redirections(current_cmd, &fds, data);
		if (current_cmd->cmd && current_cmd->cmd[0])
		{
			if (!is_builtin_command(data, current_cmd))
				execute_process(data, current_cmd, &fds);
		}
		close_fds_parent(&fds);
		fds.input = fds.pipes[0];
		if (!current_cmd->next)
			close_fds_parent(&fds);
		if (current_cmd->next)
			current_cmd->next->prev = current_cmd;
		current_cmd = current_cmd->next;
	}
	wait_child(data);
	close_all_fds(&fds);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olardeux <olardeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 15:38:02 by olardeux          #+#    #+#             */
/*   Updated: 2024/11/25 06:14:10 by olardeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_status = 0;

void	print_cmd_list(t_cmd_list *cmd_list)
{
	t_cmd_list	*tmp;
	t_redir		*redir;
	int			i;

	tmp = cmd_list;
	while (tmp)
	{
		printf("cmd: %s\n", tmp->cmd);
		i = 0;
		redir = tmp->redir;
		while (redir)
		{
			printf("type = %d redir: %s\n", redir->type, redir->file);
			redir = redir->next;
		}
		while (tmp->args[i])
		{
			printf("args[%d]: %s\n", i, tmp->args[i]);
			i++;
		}
		tmp = tmp->next;
	}
}

int	exec(t_data *data)
{
	pid_t	pid;
	int		status;
	char	**envp;

	if (is_builtin(data->cmd_list))
		return (builtin(data));
	data->cmd_list->cmd = get_env_exec(data->env, data->cmd_list->cmd);
	envp = env_to_array(data->env);
	pid = fork();
	if (pid == 0)
	{
		execve(data->cmd_list->cmd, data->cmd_list->args, envp);
		error_msg(NO_CMD, data->cmd_list->cmd);
		free_tab(envp);
		free_cmd_list(data->cmd_list);
		free_env(data->env);
		exit(1);
	}
	else
		waitpid(pid, &status, 0);
	free_tab(envp);
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	(void)argc;
	(void)argv;
	signal_init();
	data.env = init_env(envp);
	rl_initialize();
	while (1)
	{
		data.line = readline(PROMPT);
		if (!data.line)
			break ;
		if (data.line[0] != '\0')
		{
			add_history(data.line);
			data.cmd_list = parsing(&data.line, data.env);
			if (data.cmd_list)
			{
				print_cmd_list(data.cmd_list);
				exec(&data);
				free_cmd_list(data.cmd_list);
			}
			free(data.line);
		}
	}
	free_env(data.env);
	rl_clear_history();
	return (0);
}

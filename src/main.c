/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olardeux <olardeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 15:38:02 by olardeux          #+#    #+#             */
/*   Updated: 2024/10/14 09:54:00 by olardeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_cmd_list(t_cmd_list *cmd_list)
{
	t_cmd_list	*tmp;
	int			i;

	tmp = cmd_list;
	while (tmp)
	{
		printf("cmd: %s\n", tmp->cmd);
		printf("output: %s\n", tmp->output);
		i = 0;
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
	envp = env_to_array(data->env);
	pid = fork();
	if (pid == 0)
	{
		execve(data->cmd_list->cmd, data->cmd_list->args, envp);
		error_msg(NO_CMD, data->cmd_list->cmd);
		free_tokens(envp);
		free_cmd_list(data->cmd_list);
		free_env(data->env);
		exit(1);
	}
	else
		waitpid(pid, &status, 0);
	free_tokens(envp);
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	(void)argc;
	(void)argv;
	signal_init();
	data.env = init_env(envp);
	if (!data.env)
		return (1);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marida-c <marida-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 15:38:02 by olardeux          #+#    #+#             */
/*   Updated: 2024/12/02 12:11:57 by marida-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_sig = 0;

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

void	init_data(t_data *data)
{
	data->cmd_list = NULL;
	data->env = NULL;
	data->line = NULL;
	data->excode = 0;
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	((void)argc, (void)argv);
	(init_data(&data), init_sig());
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
			data.cmd_list = parsing(&data);
			if (data.cmd_list)
			{
				exec(&data);
				free_cmd_list(data.cmd_list);
			}
			free(data.line);
		}
	}
	(free_env(data.env), rl_clear_history());
	return (0);
}

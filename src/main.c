/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olardeux <olardeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 15:38:02 by olardeux          #+#    #+#             */
/*   Updated: 2024/09/25 09:26:14 by olardeux         ###   ########.fr       */
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

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	t_cmd_list	*cmd_list;
	t_env		*env;

	(void)argc;
	(void)argv;
	env = init_env(envp);
	if (!env)
		return (1);
	rl_initialize();
	while (1)
	{
		line = readline(PROMPT);
		if (!line)
			break ;
		if (ft_strncmp(line, "exit", 4) == 0)
		{
			free(line);
			break ;
		}
		if (line[0] != '\0')
		{
			add_history(line);
			cmd_list = parsing(&line, env);
			if (cmd_list)
			{
				print_cmd_list(cmd_list);
				free_cmd_list(cmd_list);
			}
			free(line);
		}
	}
	free_env(env);
	rl_clear_history();
	return (0);
}

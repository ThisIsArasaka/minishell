/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olardeux <olardeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 15:38:02 by olardeux          #+#    #+#             */
/*   Updated: 2024/08/27 11:14:05 by olardeux         ###   ########.fr       */
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

	// int pid;
	(void)argc;
	(void)argv;
	(void)envp;
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
			cmd_list = parsing(&line);
			if (!cmd_list)
				break ;
			print_cmd_list(cmd_list);
			free(line);
			free_cmd_list(cmd_list);
		}
	}
	rl_clear_history();
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olardeux <olardeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 15:38:02 by olardeux          #+#    #+#             */
/*   Updated: 2024/08/23 09:55:09 by olardeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char *line;
	t_cmd_list *cmd_list;
	int pid;

	(void)argc;
	(void)argv;
	rl_initialize();
	while (1)
	{
		line = readline(PROMPT);
		if (!line)
			break ;
		if (line[0] != '\0')
		{
			add_history(line);
		}
		free(line);
	}
	return (0);
}
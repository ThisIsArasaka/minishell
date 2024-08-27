/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olardeux <olardeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 13:48:43 by olardeux          #+#    #+#             */
/*   Updated: 2024/08/26 12:54:41 by olardeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd_list(t_cmd_list *cmd_list)
{
	t_cmd_list	*tmp;
	int			i;

	i = 0;
	while (cmd_list)
	{
		tmp = cmd_list;
		cmd_list = cmd_list->next;
		free(tmp->cmd);
		free(tmp->output);
		while (tmp->args[i])
		{
			free(tmp->args[i]);
			i++;
		}
		i = 0;
		free(tmp->args);
		free(tmp);
	}
}

void	free_tokens(char **tokens)
{
	int i;

	i = 0;
	while (tokens[i])
	{
		free(tokens[i]);
		i++;
	}
	free(tokens);
}
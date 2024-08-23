/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olardeux <olardeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 09:13:15 by olardeux          #+#    #+#             */
/*   Updated: 2024/08/23 16:44:49 by olardeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// t_cmd_list	*parse(char *line)
// {
// 	t_cmd_list *cmd_list;
// 	t_cmd_list *tmp;
// 	int i;
// 	int in_quote;

// 	i = 0;
// 	in_quote = 0;
// 	cmd_list = malloc(sizeof(t_cmd_list));
// 	cmd_list->cmd = NULL;
// 	cmd_list->args = NULL;
// 	cmd_list->next = NULL;
// 	while (line[i])
// 	{
// 		if (!ft_isblank(line[i]) && !in_quote)
// 		{
// 			if (!cmd_list->cmd)
// 			{
// 				cmd_list->cmd = ft_substr(line, i, word_len(line + i, ' '));
// 				cmd_list->args = malloc(sizeof(char *) * (words_count(line + i,
// 								'|') + 1));
// 				i += word_len(line + i, ' ');
// 			}

// 		}
// 		i++;
// 	}
// }
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrn <mrn@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 15:38:02 by olardeux          #+#    #+#             */
/*   Updated: 2024/11/29 18:08:56 by mrn              ###   ########.fr       */
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

	(void)argc;
	(void)argv;
	init_data(&data);
	init_sig();
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
	free_env(data.env);
	rl_clear_history();
	return (0);
}
// void print_cmd_list(t_cmd_list *cmd_list)
// {
//     t_cmd_list *tmp;
//     int i;

//     tmp = cmd_list;
//     while (tmp)
//     {
// 		if (!cmd_list)
//     	{
//         	printf("cmd_list is NULL\n");
//         	return ;
//    		}
//     	printf("cmd_list is valid...\n");
//
// Vérifiez que tmp->cmd et tmp->output ne sont pas NULL avant de les afficher
//         if (tmp->cmd != NULL)
// 		{
// 			printf("ok\n");
// 			printf("cmd: %s\n", tmp->cmd);
// 		}
//         else
//             printf("cmd: (null)\n");
//         if (tmp->output != NULL)
//             printf("output: %s\n", tmp->output);
//         else
//             printf("output: (null)\n");
//         i = 0;
//         while (tmp->args && tmp->args[i])
//         {
//             if (tmp->args[i] != NULL)
//                 printf("args[%d]: %s\n", i, tmp->args[i]);
//             else
//                 printf("args[%d]: (null)\n", i);
//             i++;
//         }
//         tmp = tmp->next;
//     }
// }

// void test_cmd_node(t_cmd_list *node)
// {
//     if (!node)
//     {
//         printf("Node is NULL\n");
//         return ;
//     }

//     printf("Node at address: %p\n", (void *)node);

//     if (node->cmd)
//         printf("cmd: %s\n", node->cmd);
//     else
//         printf("cmd is NULL\n");

//     if (node->output)
//         printf("output: %s\n", node->output);
//     else
//         printf("output is NULL\n");

//     if (node->args)
//     {
//         int i = 0;
//         while (node->args[i])
//         {
//             printf("args[%d]: %s\n", i, node->args[i]);
//             i++;
//         }
//     }
//     else
//     {
//         printf("args is NULL\n");
//     }
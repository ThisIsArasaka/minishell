/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olardeux <olardeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 08:13:16 by olardeux          #+#    #+#             */
/*   Updated: 2024/11/29 10:18:26 by olardeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_data *data, t_cmd_list *cmd)
{
	char	*pwd;

	if (cmd->args[1])
		return (data->excode = 1, error_msg("pwd", "too many arguments"), 1);
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (error_msg(NO_FILE, NULL), 0);
	printf("%s\n", pwd);
	free(pwd);
	return (1);
}

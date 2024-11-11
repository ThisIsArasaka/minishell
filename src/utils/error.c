/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olardeux <olardeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 09:47:17 by olardeux          #+#    #+#             */
/*   Updated: 2024/10/20 23:43:45 by olardeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_msg(char *msg, char *arg)
{
	if (!arg)
		printf("minishell: %s\n", msg);
	else
		printf("minishell: %s: %s\n", msg, arg);
}

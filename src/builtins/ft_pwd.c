/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrn <mrn@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 08:13:16 by olardeux          #+#    #+#             */
/*   Updated: 2024/11/21 15:35:40 by mrn              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(void)
{
	printf(PURPLE"executing pwd...\n"RESET);
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (error_msg(NO_FILE, NULL), 0);
	printf("%s\n", pwd);
	free(pwd);
	return (1);
}

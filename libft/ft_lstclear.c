/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olardeux <olardeux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 13:03:40 by olardeux          #+#    #+#             */
/*   Updated: 2023/11/24 14:54:58 by olardeux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*act;
	t_list	*save;

	if (!lst || !del)
		return ;
	act = *lst;
	while (act)
	{
		save = act->next;
		ft_lstdelone(act, del);
		act = save;
	}
	*lst = NULL;
}

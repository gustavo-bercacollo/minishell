/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klima-do <klima-do@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 15:30:06 by klima-do          #+#    #+#             */
/*   Updated: 2025/09/30 16:51:25 by klima-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*node;

	if (!lst || !del || !*lst)
		return ;
	while (*lst)
	{
		node = (*lst)->next;
		del((*lst)->content);
		free(*lst);
		*lst = node;
	}
}

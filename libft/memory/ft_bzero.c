/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klima-do <klima-do@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 18:14:49 by klima-do          #+#    #+#             */
/*   Updated: 2025/09/30 16:51:25 by klima-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include <stdio.h>

void	ft_bzero(void *s, size_t n)
{
	char	*ptr;
	size_t	index;

	ptr = s;
	index = 0;
	while (index < n)
	{
		ptr[index] = 0;
		index++;
	}
}

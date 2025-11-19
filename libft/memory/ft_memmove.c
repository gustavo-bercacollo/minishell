/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klima-do <klima-do@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 14:32:07 by klima-do          #+#    #+#             */
/*   Updated: 2025/10/01 16:41:55 by klima-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include <stdio.h>
#include <string.h>

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;
	size_t			index;

	if (dest == src || n == 0)
		return (dest);
	d = (unsigned char *) dest;
	s = (unsigned char *) src;
	index = 0;
	if (d >= s)
	{
		d += n - 1;
		s += n - 1;
		while (n--)
		*d-- = *s--;
	}
	else
	{
		while (n--)
		*d++ = *s++;
	}
	return (dest);
}

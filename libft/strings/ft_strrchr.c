/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klima-do <klima-do@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 19:57:17 by klima-do          #+#    #+#             */
/*   Updated: 2025/09/30 16:51:25 by klima-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*last_ocurrence;
	char	value;
	size_t	index;

	index = 0;
	value = (char) c;
	last_ocurrence = NULL;
	while (1)
	{
		if (s[index] == value)
		{
			last_ocurrence = (char *)&s[index];
		}
		if (s[index] == '\0')
		{
			break ;
		}
		index++;
	}
	return (last_ocurrence);
}

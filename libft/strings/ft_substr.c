/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klima-do <klima-do@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 18:08:34 by klima-do          #+#    #+#             */
/*   Updated: 2025/09/30 16:51:25 by klima-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	string_size;
	size_t	index;

	string_size = ft_strlen(s);
	index = 0;
	if (!s)
		return (NULL);
	if (start > string_size)
		start = string_size;
	if (len > string_size - start)
		len = string_size - start;
	ptr = malloc(len + 1);
	if (!ptr)
		return (NULL);
	while (len && s[start])
	{
		ptr[index] = s[start];
		index++;
		start++;
		len--;
	}
	ptr[index] = '\0';
	return (ptr);
}

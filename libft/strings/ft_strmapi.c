/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klima-do <klima-do@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 15:31:24 by klima-do          #+#    #+#             */
/*   Updated: 2025/09/30 16:51:25 by klima-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	size;
	size_t	index;
	char	*ptr;

	if (!s || !f)
		return (NULL);
	size = ft_strlen(s);
	index = 0;
	ptr = malloc(size + 1);
	if (!ptr)
		return (NULL);
	while (s[index])
	{
		ptr[index] = f(index, s[index]);
		index++;
	}
	ptr[size] = '\0';
	return (ptr);
}

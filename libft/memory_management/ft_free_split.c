/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klima-do <klima-do@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 17:58:35 by klima-do          #+#    #+#             */
/*   Updated: 2025/11/17 17:59:32 by klima-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	**ft_free_split(char **arr_ptr)
{
	int	index;

	index = 0;
	if (!arr_ptr)
		return (NULL);
	while (arr_ptr[index])
	{
		free(arr_ptr[index]);
		index++;
	}
	free(arr_ptr);
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klima-do <klima-do@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 20:39:01 by klima-do          #+#    #+#             */
/*   Updated: 2025/09/30 16:51:25 by klima-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static char	*ft_free_and_join(char *storage, char *buf)
{
	char	*temp;

	temp = ft_strjoin(storage, buf);
	free(storage);
	return (temp);
}

static char	*read_file(int fd, char *response)
{
	int		bytes_read;
	char	*buffer;

	bytes_read = 1;
	if (!response)
		response = (ft_calloc(1, 1));
	if (response && ft_strchr(response, '\n'))
		return (response);
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(response);
			free(buffer);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		response = ft_free_and_join(response, buffer);
		if (ft_strchr(response, '\n'))
			break ;
	}
	free(buffer);
	return (response);
}

static char	*extract_line(char	*storage)
{
	int		index;
	char	*line;

	index = 0;
	if (!storage[index])
		return (NULL);
	while (storage[index] && storage[index] != '\n')
		index++;
	line = ft_calloc(index + 2, sizeof(char));
		index = 0;
	while (storage[index] && storage[index] != '\n')
	{
		line[index] = storage[index];
		index++;
	}
	if (storage[index] && storage[index] == '\n')
		line[index++] = '\n';
	return (line);
}

static char	*ft_next_line(char *buffer)
{
	int		index;
	int		index2;
	char	*next;

	index = 0;
	while (buffer[index] && buffer[index] != '\n')
		index++;
	if (!buffer[index])
	{
		free(buffer);
		return (NULL);
	}
	next = ft_calloc((ft_strlen(buffer) - index) + 1, sizeof(char));
	if (!next)
	{
		free (buffer);
		return (NULL);
	}
	index++;
	index2 = 0;
	while (buffer[index])
		next[index2++] = buffer[index++];
	free(buffer);
	return (next);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = read_file(fd, buffer);
	if (!buffer)
		return (NULL);
	line = extract_line(buffer);
	buffer = ft_next_line(buffer);
	return (line);
}

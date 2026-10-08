/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaabed <yaabed@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 12:18:06 by yaabed            #+#    #+#             */
/*   Updated: 2026/10/08 18:33:49 by yaabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stddef.h>
#include <stdlib.h>

char	*edit_stash(char *stash, char *line)
{
	size_t	index;
	size_t	new_index;
	char	*new_stash;

	if (!stash)
		return (NULL);
	new_stash = malloc(ft_strlen(stash) - ft_strlen(line) + 1);
	if (!new_stash)
		return (NULL);
	index = 0;
	while (stash[index] != '\n' && stash[index] != '\0')
		index++;
	if (stash[index] == '\n')
		index++;
	new_index = 0;
	while (stash[index + new_index] != '\0')
	{
		new_stash[new_index] = stash[index + new_index];
		new_index++;
	}
	new_stash[new_index] = '\0';
	free(stash);
	return (new_stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*buffer;
	char		*line;
	char		*new_stash;
	ssize_t		bytes_read;

		buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	while (!ft_strchr(stash, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read > 0)
			buffer[bytes_read] = '\0';
		else if (bytes_read < 0)
		{
			free(buffer);
			free(stash);
			stash = NULL;
			return (NULL);
		}
		else
		{
			if (stash && stash[0] != '\0')
			{
				line = stash;
				free(buffer);
				stash = NULL;
				return (line);
			}
			free(stash);
			free(buffer);
			stash = NULL;
			return (NULL);
		}
		new_stash = ft_strjoin(stash, buffer);
		if (!new_stash)
		{
		free(stash);
		free(buffer);
		stash = NULL;
		return (NULL);
		}
		free(stash);
		stash = new_stash;
	}
	free(buffer);
	line = get_line(stash);
	if (line)
		new_stash = edit_stash(stash, line);
	if (!new_stash)
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	else
	{
		free(stash);
		stash = new_stash;
	}
	return (line);
}

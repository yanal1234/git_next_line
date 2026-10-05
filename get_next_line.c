/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaabed <yaabed@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 12:18:06 by yaabed            #+#    #+#             */
/*   Updated: 2026/10/05 15:32:43 by yaabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stddef.h>
#include <stdlib.h>

void	edite_stash(char **stash, char *line)
{
	size_t	index;
	size_t	new_index;
	char	*new_stash;

	if (!stash)
		return ;
	new_stash = malloc(ft_strlen(*stash) - ft_strlen(line) + 1);
	if (!new_stash)
		return ;
	index = 0;
	while ((*stash)[index] != '\n' && (*stash)[index] != '\0')
	{
		index++;
	}
	if ((*stash)[index] == '\n')
		index++;
	new_index = 0;
	while ((*stash)[index + new_index] != '\0')
	{
		new_stash[new_index] = (*stash)[index + new_index];
		new_index++;
	}
	new_stash[new_index] = '\0';
	free(*stash);
	*stash = new_stash;
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*buffer;
	char		*line;
	ssize_t		bytes_read;

	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read > 0)
		buffer[bytes_read] = '\0';
	stash = ft_strjoin(stash, buffer);
	line = get_line(stash);
	edite_stash(&stash, line);
	return (line);
}

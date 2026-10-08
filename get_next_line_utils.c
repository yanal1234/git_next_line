/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                   +:+ +:+         +:+      */
/*   By: username <username@student.42tokyo.jp>    #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/10/02 01:09:10 by username         #+#    #+#              */
/*   Updated: 2026/10/08 12:01:18 by yaabed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	number_loop;

	number_loop = 0;
	while (s[number_loop] != '\0')
	{
		number_loop += 1;
	}
	return (number_loop);
}

static size_t	insert_join(char *ptr, char const *s, size_t index_ptr, size_t index)
{
	while (s[index])
	{
		ptr[index_ptr] = s[index];
		index++;
		index_ptr++;
	}
	return (index_ptr);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	index;
	size_t	index_ptr;
	char	*ptr;

	if (!s1)
		s1 = "";
	if (!s2)
		s2 = "";
	ptr = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	index = 0;
	index_ptr = 0;
	if (!ptr)
		return (NULL);
	index_ptr = insert_join(ptr, s1, index_ptr, index);
	index = 0;
	index_ptr = insert_join(ptr, s2, index_ptr, index);
	ptr[index_ptr] = '\0';
	return (ptr);
}

char	*ft_strchr(char *s, int c)
{
	int		index;
	char	*ptr;

	if (!s)
		return (NULL);
	index = 0;
	ptr = s;
	while (ptr[index] != '\0')
	{
		if (ptr[index] == (char) c)
			return (&ptr[index]);
		index++;
	}
	if ((char) c == '\0')
		return (&ptr[index]);
	return (NULL);
}

char	*get_line(char *stash)
{
	size_t	index;
	char	*ptr;
	char	*line;

	if (!stash)
		return (NULL);
	ptr = ft_strchr(stash, '\n');
	if (!ptr)
		return (NULL);
	line = malloc((ptr - stash) + 2);
	if (!line)
		return (NULL);
	index = 0;
	while (index < (ptr - stash + 1))
	{
		line[index] = stash[index];
		index++;
	}
	line[index] = '\0';
	return (line);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanwang <hanwang@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 11:53:19 by yshi              #+#    #+#             */
/*   Updated: 2026/03/09 22:44:20 by hanwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	read_to_stash(int fd, char **stash, char *buffer)
{
	char	*tmp;
	int		bytes_read;

	bytes_read = 1;
	while (!ft_strchr(*stash, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(buffer);
			free(*stash);
			*stash = NULL;
			return (0);
		}
		if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		tmp = *stash;
		*stash = ft_strjoin(*stash, buffer);
		free(tmp);
	}
	return (1);
}

char	*get_the_line(char *stash)
{
	size_t	len;

	len = 0;
	while (stash[len] && stash[len] != '\n')
		len++;
	if (stash[len] == '\n')
		len++;
	return (ft_substr(stash, 0, len));
}

char	*clean_stash(char *stash)
{
	size_t	i;
	size_t	j;
	char	*new_stash;

	i = 0;
	j = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i])
	{
		free(stash);
		return (NULL);
	}
	i++;
	new_stash = malloc(ft_strlen(stash + i) + 1);
	if (!new_stash)
		return (free(stash), NULL);
	while (stash[i])
		new_stash[j++] = stash[i++];
	new_stash[j] = '\0';
	free(stash);
	return (new_stash);
}

char	*get_next_line(int fd)
{
	static char	*stash = NULL;
	char		*buffer;
	char		*line;

	if (fd == -1)
		return (free(stash), stash = NULL, NULL);
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	if (!read_to_stash(fd, &stash, buffer))
		return (NULL);
	free(buffer);
	if (!stash || stash[0] == '\0')
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	line = get_the_line(stash);
	stash = clean_stash(stash);
	return (line);
}
// #include <fcntl.h>
// int main()
// {
// 	char	*line;
// 	int fd = open("x.txt", O_RDONLY);
// 	if (fd < 0)
// 	{
// 		return (1);
// 	}

// 	while(line = get_next_line(fd))
// 	{
// 		printf("%s", line);
// 		free(line);
// 	}
// 	close(fd);
// }

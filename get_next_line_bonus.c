/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phofer <phofer@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 16:14:53 by phofer            #+#    #+#             */
/*   Updated: 2025/06/20 16:59:17 by phofer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "get_next_line_bonus.h"

static char	*ft_strjoin_free(char *s1, const char *s2)
{
	char	*joined;

	joined = ft_strjoin(s1, s2);
	free(s1);
	return (joined);
}

static char	*trim_buf(char *buffer)
{
	size_t	i;
	size_t	j;
	char	*new_buf;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		++i;
	if (!buffer[i])
		return (free(buffer), NULL);
	new_buf = ft_calloc(ft_strlen(buffer + i + 1) + 1, sizeof(char));
	if (!new_buf)
		return (free(buffer), NULL);
	j = 0;
	++i;
	while (buffer[i])
		new_buf[j++] = buffer[i++];
	free(buffer);
	return (new_buf);
}

static char	*extract_line(char *buffer)
{
	size_t	i;
	char	*line;

	if (!buffer || !buffer[0])
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		++i;
	line = ft_calloc(i + (buffer[i] == '\n') + 1, sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		++i;
	}
	if (buffer[i] == '\n')
		line[i] = '\n';
	return (line);
}

static char	*read_to_buffer(int fd, char *buffer)
{
	char	*buff;
	ssize_t	bytes;

	if (!buffer)
		buffer = ft_calloc(1, 1);
	buff = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer || !buff)
		return (free(buffer), free(buff), NULL);
	bytes = 1;
	while (bytes > 0 && !ft_strchr(buffer, '\n'))
	{
		bytes = read(fd, buff, BUFFER_SIZE);
		if (bytes < 0)
			return (free(buffer), free(buff), NULL);
		if (bytes == 0)
			break ;
		buff[bytes] = '\0';
		buffer = ft_strjoin_free(buffer, buff);
		if (!buffer)
			return (free(buff), NULL);
		if (ft_strchr(buff, '\n'))
			break ;
	}
	free(buff);
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer[OPEN_MAX];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		free(buffer[fd]);
		buffer[fd] = NULL;
		return (NULL);
	}
	buffer[fd] = read_to_buffer(fd, buffer[fd]);
	if (!buffer[fd])
		return (NULL);
	line = extract_line(buffer[fd]);
	buffer[fd] = trim_buf(buffer[fd]);
	return (line);
}
/*
#include <fcntl.h>      // open()
#include <unistd.h>
#include <stdio.h>      // printf(), perror()
#include <stdlib.h>     // free(), exit()
#include "get_next_line_bonus.h"

int	main(int argc, char **argv)
{
	int		fd1, fd2;
	char	*line1, *line2;

	if (argc != 3)
	{
		printf("Usage: %s <file1> <file2>\n", argv[0]);
		return (1);
	}

	fd1 = open(argv[1], O_RDONLY);
	fd2 = open(argv[2], O_RDONLY);
	if (fd1 < 0 || fd2 < 0)
	{
		perror("Error opening files");
		return (1);
	}

	printf("Reading alternately from %s and %s:\n\n", argv[1], argv[2]);

	while (1)
	{
		line1 = get_next_line(fd1);
		line2 = get_next_line(fd2);

		if (!line1 && !line2)
			break;

		if (line1)
		{
			printf("%s: %s", argv[1], line1);
			free(line1);
		}
		if (line2)
		{
			printf("%s: %s", argv[2], line2);
			free(line2);
		}
	}

	close(fd1);
	close(fd2);
	return (0);
}
*/

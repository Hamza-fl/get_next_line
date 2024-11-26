/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfalati <hfalati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 10:21:53 by hfalati           #+#    #+#             */
/*   Updated: 2024/11/26 10:56:14 by hfalati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static char	*text[1024];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > INT_MAX)
		return (NULL);
	text[fd] = creat_text(fd, text[fd]);
	if (text[fd] == NULL)
		return (NULL);
	line = get_current_line(text[fd]);
	text[fd] = next_list(text[fd]);
	return (line);
}

char	*creat_text(int fd, char *str)
{
	char	*buffer;
	int		char_read;

	char_read = 1;
	buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	if (!str)
		str = ft_strdup("");
	while (char_read != 0 && (ft_strchr(str, '\n') == NULL))
	{
		char_read = read(fd, buffer, BUFFER_SIZE);
		if (char_read < 0)
		{
			free(buffer);
			free(str);
			return (NULL);
		}
		buffer[char_read] = '\0';
		str = ft_strjoin(str, buffer);
	}
	free(buffer);
	return (str);
}

char	*get_current_line(char *line)
{
	size_t	i;
	char	*new_line;

	if (ft_strlen(line) == 0)
		return (NULL);
	i = 0;
	while (line[i] != '\n' && line[i])
		i++;
	if (line[i] == '\n')
		i++;
	new_line = ft_substr(line, 0, i);
	if (!new_line)
		return (NULL);
	return (new_line);
}

char	*next_list(char *text)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	while (text[i] && text[i] != '\n')
		i++;
	if (text[i] == '\n')
		i++;
	if (text[i] == '\0')
	{
		free(text);
		return (NULL);
	}
	tmp = malloc(sizeof(char) * (ft_strlen(text + i) + 1));
	if (!tmp)
		return (NULL);
	while (text[i])
		tmp[j++] = text[i++];
	tmp[j] = '\0';
	free(text);
	return (tmp);
}

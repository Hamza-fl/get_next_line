/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfalati <hfalati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 21:40:00 by hfalati           #+#    #+#             */
/*   Updated: 2024/11/24 21:52:58 by hfalati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static t_list	*list = NULL;
	char			*line;
	int				j;

	j = 0;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	creat_list(&list, fd);
	if (list == NULL)
		return (NULL);
	line = get_current_line(list, fd);
	if (line == NULL)
	{
		dell(&list, NULL, NULL, fd);
		return (NULL);
	}
	next_list(&list, &j, fd);
	return (line);
}

void	creat_list(t_list **list, int fd)
{
	int		char_read;
	char	*buf;

	while (!found_newline(*list, fd))
	{
		buf = malloc(BUFFER_SIZE + 1);
		if (buf == NULL)
		{
			dell(list, NULL, NULL, fd);
			return ;
		}
		char_read = read(fd, buf, BUFFER_SIZE);
		if (char_read <= 0)
		{
			free(buf);
			if (char_read < 0)
				dell(list, NULL, NULL, fd);
			return ;
		}
		buf[char_read] = '\0';
		add_back(list, buf, fd);
	}
}

void	add_back(t_list **list, char *buf, int fd)
{
	t_list	*new_node;
	t_list	*last_node;

	last_node = find_last_node(*list, fd);
	new_node = malloc(sizeof(t_list));
	if (!new_node)
	{
		dell(list, NULL, NULL, fd);
		free(buf);
		return ;
	}
	if (!last_node)
		*list = new_node;
	else
		last_node->next = new_node;
	new_node->str_buf = buf;
	new_node->fd = fd;
	new_node->next = NULL;
}

char	*get_current_line(t_list *list, int fd)
{
	int		str_len;
	char	*next_str;

	if (!list)
		return (0);
	str_len = after_new_line(list, fd);
	next_str = malloc(str_len + 1);
	if (!next_str)
		return (0);
	copy_str(list, next_str, fd);
	return (next_str);
}

void	next_list(t_list **list, int *j, int fd)
{
	t_list	*last_node;
	t_list	*clean_node;
	char	*buf;
	int		i;

	buf = malloc(BUFFER_SIZE + 1);
	clean_node = malloc(sizeof(t_list));
	if (!clean_node || !buf)
	{
		free(buf);
		free(clean_node);
		dell(list, NULL, NULL, fd);
		return ;
	}
	last_node = find_last_node(*list, fd);
	i = 0;
	while (last_node->str_buf[i] && last_node->str_buf[i] != '\n')
		i++;
	while (last_node->str_buf[i] && last_node->str_buf[++i])
		buf[(*j)++] = last_node->str_buf[i];
	buf[*j] = '\0';
	clean_node->str_buf = buf;
	clean_node->fd = fd;
	clean_node->next = NULL;
	dell(list, clean_node, buf, fd);
}

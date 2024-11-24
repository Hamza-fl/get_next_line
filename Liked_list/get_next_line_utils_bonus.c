/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfalati <hfalati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 21:39:55 by hfalati           #+#    #+#             */
/*   Updated: 2024/11/24 21:52:36 by hfalati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int found_newline(t_list *list, int fd)
{
	if (!list)
		return (0);
	while (list)
	{
		if (list->fd == fd)
		{
			int i = 0;
			while (list->str_buf[i] && i < BUFFER_SIZE)
				if (list->str_buf[i++] == '\n')
					return (1);
		}
		list = list->next;
	}
	return (0);
}

t_list *find_last_node(t_list *list, int fd)
{
	t_list *last;

	if (!list)
		return (0);
	last = NULL;
	while (list)
	{
		if (list->fd == fd)
			last = list;
		list = list->next;
	}
	return (last);
}

int after_new_line(t_list *list, int fd)
{
	int len;

	if (!list)
		return (0);
	len = 0;
	while (list)
	{
		if (list->fd == fd)
			for (int i = 0; list->str_buf[i]; i++)
			{
				if (list->str_buf[i] == '\n')
					return (++len);
				++len;
			}
		list = list->next;
	}
	return (len);
}

void copy_str(t_list *list, char *next_str, int fd)
{
	int j;

	if (!list)
		return;
	j = 0;
	while (list)
	{
		if (list->fd == fd)
			for (int i = 0; list->str_buf[i]; i++)
			{
				if (list->str_buf[i] == '\n')
				{
					next_str[j++] = '\n';
					next_str[j] = '\0';
					return;
				}
				next_str[j++] = list->str_buf[i];
			}
		list = list->next;
	}
	next_str[j] = '\0';
}

void dell(t_list **list, t_list *clean_node, char *buf, int fd)
{
	t_list *current, *prev, *tmp;

	if (!list)
	{
		free(clean_node);
		return (free(buf), (void)0);
	}
	for (current = *list, prev = NULL; current; )
	{
		if (current->fd == fd)
		{
			tmp = current->next;
			(prev) ? (prev->next = tmp) : (*list = tmp);
			free(current->str_buf);
			free(current);
			current = tmp;
			continue;
		}
		prev = current;
		current = current->next;
	}
	if (clean_node && buf && buf[0])
		clean_node->next = *list, *list = clean_node;
	else
		free(buf), free(clean_node);
}

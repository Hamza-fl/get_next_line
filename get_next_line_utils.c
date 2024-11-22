/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfalati <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 19:08:18 by hfalati           #+#    #+#             */
/*   Updated: 2024/11/20 19:08:22 by hfalati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	found_newline(t_list *list)
{
	int	i;

	if (!list)
		return (0);
	while (list)
	{
		i = 0;
		while (list->str_buf[i] && i < BUFFER_SIZE)
		{
			if (list->str_buf[i] == '\n')
				return (1);
			i++;
		}
		list = list->next;
	}
	return (0);
}

t_list	*find_last_node(t_list *list)
{
	if (!list)
		return (0);
	while (list->next)
		list = list->next;
	return (list);
}

int	after_new_line(t_list *list)
{
	int	i;
	int	len;

	if (!list)
		return (0);
	len = 0;
	while (list)
	{
		i = 0;
		while (list->str_buf[i])
		{
			if (list->str_buf[i] == '\n')
			{
				++len;
				return (len);
			}
			++i;
			++len;
		}
		list = list->next;
	}
	return (len);
}

void	copy_str(t_list *list, char *next_str)
{
	int	i;
	int	j;

	if (!list)
		return ;
	j = 0;
	while (list)
	{
		i = 0;
		while (list->str_buf[i])
		{
			if (list->str_buf[i] == '\n')
			{
				next_str[j++] = '\n';
				next_str[j] = '\0';
				return ;
			}
			next_str[j++] = list->str_buf[i++];
		}
		list = list->next;
	}
	next_str[j] = '\0';
}

void	dell(t_list **list, t_list *clean_node, char *buf)
{
	t_list	*tmp;

	if (!list)
	{
		free(clean_node);
		free(buf);
		return ;
	}
	while (*list)
	{
		tmp = (*list)->next;
		free((*list)->str_buf);
		free(*list);
		*list = tmp;
	}
	*list = NULL;
	if (clean_node && buf && buf[0])
		*list = clean_node;
	else
	{
		free(buf);
		free(clean_node);
	}
}

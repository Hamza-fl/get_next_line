/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfalati <hfalati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 19:11:37 by hfalati           #+#    #+#             */
/*   Updated: 2024/11/25 15:15:03 by hfalati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

typedef struct s_list
{
	char			*str_buf;
	struct s_list	*next;
}					t_list;

int		found_newline(t_list *list);
t_list	*find_last_node(t_list *list);
int		after_new_line(t_list *list);
void	copy_str(t_list *list, char *next_str);
void	dell(t_list **list, t_list *clean_node, char *buf);
char	*get_next_line(int fd);
void	creat_list(t_list **list, int fd);
void	add_back(t_list **list, char *buf);
char	*get_current_line(t_list *list);
void	next_list(t_list **list, int *j);

#endif

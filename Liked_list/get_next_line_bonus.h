/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfalati <hfalati@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 21:40:09 by hfalati           #+#    #+#             */
/*   Updated: 2024/11/24 21:40:11 by hfalati          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

typedef struct s_list
{
	char			*str_buf;
	int				fd;
	struct s_list	*next;
}					t_list;

int		found_newline(t_list *list, int fd);
t_list	*find_last_node(t_list *list, int fd);
int		after_new_line(t_list *list, int fd);
void	copy_str(t_list *list, char *next_str, int fd);
void	dell(t_list **list, t_list *clean_node, char *buf, int fd);
char	*get_next_line(int fd);
void	creat_list(t_list **list, int fd);
void	add_back(t_list **list, char *buf, int fd);
char	*get_current_line(t_list *list, int fd);
void	next_list(t_list **list, int *j, int fd);

#endif
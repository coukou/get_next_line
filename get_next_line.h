/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spopieul <spopieul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/16 19:41:55 by spopieul          #+#    #+#             */
/*   Updated: 2018/01/12 13:04:39 by spopieul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <sys/types.h>
# include <fcntl.h>

# include "libft.h"

# define BUFF_SIZE 4096

struct	s_cb
{
	void	*buf;
	void	*end;
	size_t	content_size;
	void	*head;
	void	*tail;
};
typedef struct s_cb	t_cb;

struct	s_fdstate
{
	int		fd;
	t_cb	*cb;
};
typedef struct s_fdstate	t_fdstate;

int		get_next_line(const int fd, char **line);

#endif

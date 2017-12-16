/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spopieul <spopieul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/16 19:41:55 by spopieul          #+#    #+#             */
/*   Updated: 2017/12/16 20:10:24 by spopieul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#include <sys/types.h>
#include <fcntl.h>

#include "libft.h"

#define BUFF_SIZE 32

struct s_cb
{
	void	*start;
	void	*end;
	size_t	content_size;
	void	*head;
	void	*tail;
};

typedef struct s_cb t_cb;

int		get_next_line(const int fd, char **line);

#endif

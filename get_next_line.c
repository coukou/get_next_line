/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spopieul <spopieul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/16 19:41:05 by spopieul          #+#    #+#             */
/*   Updated: 2017/12/16 20:28:47 by spopieul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_cb_read(t_cb *cb, void *data, size_t size)
{
	int max = cb->end - cb->tail;

	while (size > max)
	{
		ft_memcpy(data, cb->tail, max);
		size -= max;
		cb->tail = cb->start;
		cb->content_size -= max;
	}
	if (size < max)
	{
		ft_memcpy(data, cb->tail, size);
		cb->tail += size;
		cb->content_size -= size;
	}
	if (cb->tail == cb->end)
		cb->tail = cb->start;
}

void	ft_cb_write(t_cb *cb, void *data, size_t size)
{
	int max = cb->end - cb->head;

	while (size > max)
	{
		ft_memcpy(cb->head, data, max);
		size -= max;
		cb->head = cb->start;
		cb->content_size += max;
	}
	if (size < max)
	{
		ft_memcpy(cb->head, data, size);
		cb->head += size;
		cb->content_size += size;
	}
	if (cb->head == cb->end)
		cb->head = cb->start;
}

int		flush_line(t_cb *cb, char **line)
{
	int i;
	char data;

	i = -1;
	data = 0;
	while (cb->content_size > 0)
	{
		ft_cb_read(cb, &data, 1);
		if (data == '\n')
			return (1);
		(*line)[++i] = data;
	}
	return (0);
}

t_cb	*ft_cb_init(size_t size)
{
	t_cb *cb;

	cb = ft_memalloc(sizeof(*cb));
	if (cb == NULL)
		return (NULL);
	cb->start = ft_memalloc(size);
	if (cb->start == NULL)
		return (NULL);
	cb->end = cb->start + size;
	cb->content_size = 0;
	cb->head = cb->start;
	cb->tail = cb->start;
	ft_cb_write(cb, "helloda\nsdas das\ndsada", 22);
	return (cb);
}

int		get_next_line(const int fd, char **line)
{
	static t_cb *cb;

	if (cb == NULL)
		cb = ft_cb_init(BUFF_SIZE);
	*line = ft_strnew(50);
	if (flush_line(cb, line))
		return (1);
	return (0);
}

int main()
{
	char *line;

	get_next_line(0, &line);
	get_next_line(0, &line);
	get_next_line(0, &line);
	ft_putendl(line);
}

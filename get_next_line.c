/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spopieul <spopieul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/16 19:41:05 by spopieul          #+#    #+#             */
/*   Updated: 2018/01/09 20:38:01 by spopieul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_cb_read(t_cb *cb, void *data, size_t size)
{
	size_t max;

	max = cb->end - cb->tail;
	while (size > max)
	{
		ft_memcpy(data, cb->tail, max);
		size -= max;
		cb->tail = cb->buf;
		cb->content_size -= max;
		data += max;
	}
	if (size <= max)
	{
		ft_memcpy(data, cb->tail, size);
		cb->tail += size;
		cb->content_size -= size;
		data += size;
	}
	if (cb->tail == cb->end)
		cb->tail = cb->buf;
}

void	ft_cb_write(t_cb *cb, void *data, size_t size)
{
	size_t max;

	max = cb->end - cb->head;
	while (size > max)
	{
		ft_memcpy(cb->head, data, max);
		size -= max;
		cb->head = cb->buf;
		cb->content_size += max;
		data += max;
	}
	if (size <= max)
	{
		ft_memcpy(cb->head, data, size);
		cb->head += size;
		cb->content_size += size;
		data += size;
	}
	if (cb->content_size > (size_t)(cb->end - cb->buf))
		cb->content_size = cb->end - cb->buf;
	if (cb->head == cb->end)
		cb->head = cb->buf;
}

t_fdstate	*ft_get_fdstate(t_list **fdstate_lst, const int fd)
{
	t_list *tmp;
	t_list *new;
	t_fdstate *state;

	tmp = *fdstate_lst;
	while (tmp)
	{
		if (tmp->content && ((t_fdstate*)tmp->content)->fd == fd)
			return ((t_fdstate*)tmp->content);
		tmp = tmp->next;
	}
	if (!(new = ft_memalloc(sizeof(*new))))
		return (NULL);
	if (!(new->content = ft_memalloc(sizeof(t_fdstate))))
		return (NULL);
	state = new->content;
	state->fd = fd;
	if (!(state->cb = ft_memalloc(sizeof(*state->cb))) ||
		!(state->cb->buf = ft_memalloc(BUFF_SIZE)))
		return (NULL);
	state->cb->end = state->cb->buf + BUFF_SIZE;
	state->cb->head = state->cb->buf;
	state->cb->tail = state->cb->buf;
	ft_lstadd(fdstate_lst, new);
	return (ft_get_fdstate(fdstate_lst, fd));
}

int			get_next_line2(t_fdstate *state, char **line, char *tmp)
{
	size_t i;
	int c;
	int ret;
	char buf[BUFF_SIZE];
	char *line_tmp;

	i = 0;
	tmp = ft_strnew(state->cb->content_size);
	while (!(c = 0) && state->cb->content_size > 0)
	{
		ft_cb_read(state->cb, &c, 1);
		if (c == '\n')
			break ;
		tmp[i++] = c;
	}
	line_tmp = *line;
	*line = ft_strjoin(*line, tmp);
	ft_strdel(&tmp);
	ft_strdel(&line_tmp);
	if (c == '\n')
		return (1);
	if ((ret = read(state->fd, buf, BUFF_SIZE)) <= 0)
		return ((ret == 0 && **line != 0) ? 1 : ret);
	ft_cb_write(state->cb, buf, ret);
	return (get_next_line2(state, line, tmp));
}

int			get_next_line(const int fd, char **line)
{
	static t_list 	*fdstate_lst;
	t_fdstate		*state;
	int				ret;

	if (fd < 0 || line == NULL)
		return (-1);
	if (fdstate_lst == NULL)
	{
		fdstate_lst = ft_memalloc(sizeof(*fdstate_lst));
		if (fdstate_lst == NULL)
			return (-1);
	}
	state = ft_get_fdstate(&fdstate_lst, fd);
	if (state == NULL)
		return (-1);
	*line = ft_strnew(0);
	if (*line == NULL)
		return (-1);
	ret = get_next_line2(state, line, NULL);
	if (ret <= 0)
		ft_strdel(line);
	return (ret);
}

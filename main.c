/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spopieul <spopieul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 20:38:57 by spopieul          #+#    #+#             */
/*   Updated: 2018/01/09 20:48:37 by spopieul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int main(void)
{
	int i = 0;
	char *line;

	while (++i < 5000 && get_next_line(0, &line) > 0)
	{
		ft_putendl(line);
		ft_strdel(&line);
	}
}

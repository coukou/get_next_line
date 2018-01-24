/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spopieul <spopieul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/12 13:52:58 by spopieul          #+#    #+#             */
/*   Updated: 2018/01/12 13:54:01 by spopieul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int main()
{
	int i = 0;
	char *line;

	while (get_next_line(0, &line))
	{
		ft_putendl(line);
		ft_strdel(&line);
	}
}
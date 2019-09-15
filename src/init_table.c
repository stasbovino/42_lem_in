/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwyman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 18:16:49 by gwyman-m          #+#    #+#             */
/*   Updated: 2019/09/16 01:27:11 by sts              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		find_no_room(char *s)
{
	int i;

	i = -1;
	if (s[0] == '#')
		return (2);
	while (s[++i])
		if (s[i] == '-')
			return (1);
	return (0);
}

int		count_rooms(char **input, int size)
{
	int i;
	int	count;
	int	ret;

	count = 0;
	i = 0;
	while (++i < size)
	{
		ret = find_no_room(input[i]);
		if (ret == 1)
			break;
		if (ret == 0)
			count++;
	}
	return (count);
}

int		create_table(char **input, int size)
{
	int	rooms;

	rooms = count_rooms(input, size);
	ft_printf("rooms: %d\n", rooms);
	if (rooms == 0)
		return (1);
	return (0);
}

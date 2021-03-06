/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_links.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwyman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 20:05:28 by gwyman-m          #+#    #+#             */
/*   Updated: 2019/10/11 18:01:00 by gwyman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	set_coords(int ***int_table, char **table, char **rooms)
{
	int j;
	int a;
	int b;

	j = -1;
	a = 0;
	b = 0;
	while (table[++j])
	{
		if (ft_strcmp(table[j], rooms[0]) == 0)
			a = j + 1;
		else if (ft_strcmp(table[j], rooms[1]) == 0)
			b = j + 1;
		if (a != 0 && b != 0)
			break ;
	}
	(*int_table)[a][b] = 1;
	(*int_table)[b][a] = 1;
}

int			create_links(int ***int_table, char **table, char **input, int size)
{
	int		i;
	char	**rooms;

	i = 0;
	while (input[i] && (input[i][0] == '#' || count_chars(input[i]) == 0))
		i++;
	i--;
	while (++i < size)
	{
		if (input[i][0] == '#')
			continue ;
		if (!(rooms = ft_strsplit(input[i], '-')))
			return (1);
		set_coords(int_table, table, rooms);
		free_split(&rooms, 2, 0);
	}
	return (0);
}

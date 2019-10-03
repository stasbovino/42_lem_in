/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwyman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 18:16:49 by gwyman-m          #+#    #+#             */
/*   Updated: 2019/10/03 17:09:43 by gwyman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			*free_all(char ***table, int ***int_table, int rooms, int opt)
{
	int i;

	if (table)
	{
		if (opt == -2)
		{
			free((*table)[0]);
		}
		else if (opt != -1)
		{
			i = -1;
			while (++i < opt)
			{
				free((*table)[i]);
			}
			if (opt != rooms)
				free((*table)[rooms - 1]);
		}
		free(*table);
	}
	if (int_table)
		free_tables(int_table, NULL, rooms);
	return (NULL);
}

int				**allocate_table(int rooms)
{
	int	**int_table;
	int	i;
	int	j;

	if (!(int_table = (int**)malloc(sizeof(int*) * (rooms + 2))))
		return (NULL);
	i = -1;
	while (++i < (rooms + 2))
		if (!(int_table[i] = (int*)malloc(sizeof(int) * (rooms + 2))))
		{
			j = -1;
			while (++j < i)
				free(int_table[j]);
			free(int_table);
			return (NULL);
		}
	return (int_table);
}

static void		fill_line(int **line, int start, int c, int rooms)
{
	int i;

	i = start;
	while (++i <= (rooms + 1))
		(*line)[i] = c;
}

int				**init_int_table(int rooms)
{
	int	**int_table;
	int	i;
	int	j;

	if (!(int_table = allocate_table(rooms)))
		return (NULL);
	i = 0;
	j = -1;
	while (++j < (rooms + 1))
		int_table[0][j] = j;
	int_table[0][j] = 0;
	while (++i < (rooms + 1))
		int_table[i][0] = i;
	int_table[i][0] = 0;
	i = 0;
	while (++i < (rooms + 1))
		fill_line(&int_table[i], 0, 0, rooms);
	fill_line(&int_table[i], -1, 0, rooms);
	return (int_table);
}

t_graph			*create_table(char **input, int size)
{
	int		rooms;
	char	**table;
	int		**int_table;
	int		i;
	t_graph	*g;

	rooms = count_rooms(input, size);
	if (rooms == 0 || (!(table = (char**)malloc(sizeof(char*) * (rooms + 1)))))
		return (NULL);
	i = 0;
	if (!(table[0] = get_next_room_name(input, size, 0)))
		return (free_all(&table, NULL, rooms, -1));
	if (!(table[rooms - 1] = get_next_room_name(input, size, rooms - 1)))
		return (free_all(&table, NULL, rooms, -2));
	while (++i < rooms - 1)
		if (!(table[i] = get_next_room_name(input, size, -1)))
			return (free_all(&table, NULL, rooms, i));
	table[i + 1] = NULL;
	if (!(int_table = init_int_table(rooms)))
		return (free_all(&table, NULL, rooms, rooms));
	if (create_links(&int_table, table, input, size))
		return (free_all(&table, &int_table, rooms, rooms));
	if (!(g = init_graph(table, int_table, rooms, get_ants_num(input, size))))
		return (NULL);
	return (g);
}

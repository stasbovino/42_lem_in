/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwyman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 18:16:49 by gwyman-m          #+#    #+#             */
/*   Updated: 2019/09/19 19:51:08 by gwyman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int				**allocate_table(int rooms)
{
	int	**int_table;
	int	i;

	int_table = (int**)malloc(sizeof(int*) * (rooms + 2));
	i = -1;
	while (++i < (rooms + 2))
		int_table[i] = (int*)malloc(sizeof(int) * (rooms + 2));
	return (int_table);
}

static int		**init_int_table(int rooms)
{
	int	**int_table;
	int	i;
	int	j;

	int_table = allocate_table(rooms);
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
	{
		j = 0;
		while (++j < (rooms + 1))
			int_table[i][j] = 0;
		int_table[i][j] = 0;
	}
	j = 0;
	while (++j < (rooms + 2))
		int_table[i][j] = 0;
	return (int_table);
}

static t_graph	*init_graph(char **table, int **int_table, int rooms, int ants)
{
	t_graph *graph;

	graph = (t_graph*)malloc(sizeof(t_graph));
	graph->rooms = rooms;
	graph->ants = ants;
	graph->table = int_table;
	graph->list = table;
	graph->x = 0;
	graph->paths = NULL;
	return (graph);
}

t_graph			*create_table(char **input, int size)
{
	int		rooms;
	char	**table;
	int		**int_table;
	int		i;
	t_graph	*graph;

	rooms = count_rooms(input, size);
	if (rooms == 0)
		return (NULL);
	table = (char**)malloc(sizeof(char*) * (rooms + 1));
	i = 0;
	table[0] = get_next_room_name(input, size, 0);
	table[rooms - 1] = get_next_room_name(input, size, rooms - 1);
	while (++i < rooms - 1)
		table[i] = get_next_room_name(input, size, -1);
	table[i + 1] = NULL;
	int_table = init_int_table(rooms);
	create_links(&int_table, table, input, size);
	graph = init_graph(table, int_table, rooms, get_ants_num(input, size));
	return (graph);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwyman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 18:16:49 by gwyman-m          #+#    #+#             */
/*   Updated: 2019/09/25 20:25:29 by sts              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		*free_all(char ***table, int ***int_table, int rooms, int opt)
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

	if (!(graph = (t_graph*)malloc(sizeof(t_graph))))
		return (free_all(&table, &int_table, rooms, rooms));
	graph->rooms = rooms;
	graph->ants = ants;
	graph->table = int_table;
	graph->list = table;
	graph->paths = NULL;
	graph->flows = NULL;
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
	if (!(table = (char**)malloc(sizeof(char*) * (rooms + 1))))
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
	if (!(graph = init_graph(table, int_table, rooms, get_ants_num(input, size))))
		return (NULL);
	return (graph);
}

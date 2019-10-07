/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solution.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiyellow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 18:43:27 by tiyellow          #+#    #+#             */
/*   Updated: 2019/10/07 18:06:46 by gwyman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		reweight(int **table, int *path)
{
	int	end;
	int	i;

	i = 2;
	end = path[path[0]];
	while (path[i + 1] != end)
	{
		table[path[i]][path[i + 1]] -= 1;
		table[path[i + 1]][path[i]] += 1;
		i++;
	}
}

void		restruct_table(int **table, int **begin, int rooms)
{
	int i;
	int j;

	i = 1;
	while (++i < rooms)
	{
		j = 0;
		while (++j < rooms)
		{
			if (begin[i][j] == 1 && table[i][j] != 0)
				begin[i][j] = 0;
		}
	}
}

static int	free_solution(int ***table, int ***begin, int rooms, int ret)
{
	if (table)
		free_tables(table, NULL, rooms);
	if (begin)
		free_tables(begin, NULL, rooms);
	return (ret);
}

int			find_solution(t_graph **graph)
{
	int ants;
	int	*path;
	int **table;
	int **begin;
	int rooms;
	int ret;

	ants = (*graph)->ants;
	rooms = (*graph)->rooms * 2;
	if (!(table = double_table((*graph)->table)))
		return (2);
	else if (!(begin = tab_dup(table, rooms)))
		return (free_solution(&table, NULL, rooms, 2));
	if ((ret = find_shortest_path(table, rooms, &path)) != 0)
		return (free_solution(&table, &begin, rooms, ret));
	while (ants && path)
	{
		ants--;
		reweight(table, path);
		free(path);
		if ((find_shortest_path(table, rooms, &path)) == 2)
			return (free_solution(&table, &begin, rooms, ret));
	}
	restruct_table(table, begin, rooms);
	if (path)
		free(path);
	if ((ret = create_solution(graph, begin, rooms)) != 0)
		return (free_solution(&table, &begin, rooms, ret));
	return (free_solution(&table, &begin, rooms, 0));
}

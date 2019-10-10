/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_solution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiyellow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 18:43:27 by tiyellow          #+#    #+#             */
/*   Updated: 2019/10/10 16:56:28 by sts              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	free_solution(int ***table, int ***begin, int **path, int ret)
{
	int rooms;
	int **tab;

	rooms = 1;
	tab = *table;
	while (tab[0][rooms] != 0)
		rooms++;
	rooms--;
	if (path && *path)
		free(*path);
	if (table)
		free_tables(table, NULL, rooms);
	if (begin)
		free_tables(begin, NULL, rooms);
	restore_table(NULL, rooms, 1);
	return (ret);
}

static int	check_flows(int *flows)
{
	int i;

	i = -1;
	while (flows[++i] != -1)
		if (flows[i] == 0)
			return (1);
	return (0);
}

static int	init_search(int ***table, int ***begin, int **path, t_graph *graph)
{
	int ret;
	int rooms;

	rooms = graph->rooms * 2;
	if (!(*table = double_table(graph->table)))
		return (2);
	if (!(*begin = tab_dup(*table, rooms)))
		return (free_solution(table, NULL, NULL, 2));
	if (restore_table(*begin, rooms, 0))
		return (free_solution(table, begin, NULL, 2));
	if ((ret = find_shortest_path(*table, rooms, path)) != 0)
			return (free_solution(table, begin, NULL, ret));
	return (0);
}

int			find_solution(t_graph **graph, int rooms, int ret)
{
	int	*path;
	int **table;
	int **begin;
	int *flows;
	int prev;

	if ((ret = init_search(&table, &begin, &path, *graph)) != 0)
		return (ret);
	prev = INT_MAX;
	flows = NULL;
	while (path)
	{
		reweight(table, path);
		restruct_table(table, begin, rooms);
		ret = create_solution(graph, begin, rooms, &flows);
		if (ret == -1)
		{
			free(flows);
			return (free_solution(&table, &begin, &path, ret));
		}
		free_paths(&((*graph)->paths));
		if (ret != -2 && ret <= prev && !(ret == prev && check_flows(flows)))
			prev = ret;
		else
		{
			back_weight(table, path);
			break ;
		}
		free(path);
		path = NULL;
		restore_table(begin, rooms, 0);
		if ((find_shortest_path(table, rooms, &path)) == 2)
		{
			free(flows);
			return (free_solution(&table, &begin, &path, ret));
		}
	}
	restruct_table(table, begin, rooms);
	if ((ret = create_solution(graph, begin, rooms, &flows)) == -1 || ret == -2)
	{
		free(flows);
		return (free_solution(&table, &begin, &path, ret));
	}
	ret = print_solution(*graph, flows);
	free_solution(&table, &begin, &path, 0);
	free(flows);
	if (ret == 1)
		return (-2);
	return (0);
}

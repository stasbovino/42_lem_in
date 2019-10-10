/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_solution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiyellow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 18:43:27 by tiyellow          #+#    #+#             */
/*   Updated: 2019/10/10 21:58:08 by sts              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	check_flows(int *flows)
{
	int i;

	i = -1;
	while (flows[++i] != -1)
		if (flows[i] == 0)
			return (1);
	return (0);
}

static int	new_iteration(int **path, int **table, int **begin, int rooms)
{
	free(*path);
	*path = NULL;
	restore_table(begin, rooms, 0);
	if ((find_shortest_path(table, rooms, path)) == 2)
		return (0);
	return (1);
}

static void reweight_restruct(int **table, int **begin, int *path, int rooms)
{
	reweight(table, path);
	restruct_table(table, begin, rooms);
}

static int	ret_prev_compare(int ret, int *last, int *flows)
{
	int prev;

	prev = *last;
	if (ret != -2 && ret <= prev && !(ret == prev && check_flows(flows)))
	{
		*last = ret;
		return (1);
	}
	return (0);
}

int			find_solution(t_graph **graph, int rooms, int *flows, int prev)
{
	int *path;
	int **table;
	int **begin;
	int ret;

	if ((ret = init_search(&table, &begin, &path, *graph)) != 0)
		return (ret);
	while (path)
	{
		reweight_restruct(table, begin, path, rooms);
		if ((ret = create_solution(graph, begin, rooms, &flows)) == -1)
			return (free_solution_and_flows(&table, &begin, &path, &flows));
		free_paths(&((*graph)->paths));
		if (!ret_prev_compare(ret, &prev, flows))
			if (back_weight(table, path) && !restore_table(begin, rooms, 0))
				break ;
		if (!new_iteration(&path, table, begin, rooms))
			return (free_solution_and_flows(&table, &begin, &path, &flows));
	}
	restruct_table(table, begin, rooms);
	if ((ret = create_solution(graph, begin, rooms, &flows)) == -1)
		return (free_solution_and_flows(&table, &begin, &path, &flows));
	ret = print_solution(*graph, flows);
	free_solution_and_flows(&table, &begin, &path, &flows);
	return (end_of_find_solution(ret));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solution.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiyellow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 18:43:27 by tiyellow          #+#    #+#             */
/*   Updated: 2019/10/08 03:35:41 by sts              ###   ########.fr       */
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
	int **reserve;
	int *flows;
	int previous;
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
	previous = INT_MAX;
	flows = NULL;
	while (ants && path)
	{
		ants--;
		print_path(path);
		reweight(table, path);
		free(path);
		reserve = tab_dup(begin, rooms);
		restruct_table(table, begin, rooms);
		ret = create_solution(graph, begin, rooms, &flows);
		free_tables(&begin, NULL, rooms);
		begin = reserve;
		ft_printf("prev is %d return is %d\n", previous, ret);
		if (ret == -1)
			return (-1);
		else if (ret == -2)
			break ;
		if (ret <= previous)
		{
			previous = ret;
			free_paths(&(*graph)->paths);
			(*graph)->paths = NULL;
		}
		else
			break ;
		if ((find_shortest_path(table, rooms, &path)) == 2)
			return (free_solution(&table, &begin, rooms, ret));
	}
	restruct_table(table, begin, rooms);
	create_solution(graph, begin, rooms, &flows);
	print_solution(*graph, flows);
	free_solution(&table, &begin, rooms, 0);
	free(flows);
	return (0);
}
	/*
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
	*/

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solution.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiyellow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 18:43:27 by tiyellow          #+#    #+#             */
/*   Updated: 2019/10/08 23:32:37 by sts              ###   ########.fr       */
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

void		back_weight(int **table, int *path)
{
	int	end;
	int	i;

	i = 2;
	end = path[path[0]];
	while (path[i + 1] != end)
	{
		table[path[i]][path[i + 1]] += 1;
		table[path[i + 1]][path[i]] -= 1;
		i++;
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

int			check_flows(int *flows)
{
	int i;

	i = -1;
	while (flows[++i] != -1)
		if (flows[i] == 0)
			return (1);
	return (0);
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
//		print_path(path);
		reweight(table, path);
		reserve = tab_dup(begin, rooms);
		restruct_table(table, begin, rooms);
		ret = create_solution(graph, begin, rooms, &flows);
		free_tables(&begin, NULL, rooms);
		begin = reserve;
		ft_printf("new turns are \x1b[33m%d\n\x1b[0m", ret);
		if (ret == -1)
		{
			ft_printf("\x1b[31mmalloc error\n\x1b[0m");
			return (-1);
		}
		else if (ret == -2)
		{
			ft_printf("\x1b[32mno more flows\n\x1b[0m");
			free_paths(&(*graph)->paths);
			(*graph)->paths = NULL;
			back_weight(table, path);
			break ;
		}
			free_paths(&(*graph)->paths);
			(*graph)->paths = NULL;
		if (ret <= previous && !(ret == previous && check_flows(flows)))
			previous = ret;
		else
		{
			ft_printf("\x1b[31mnew flow is worse OR zero path\n\x1b[0m");
			back_weight(table, path);
			break ;
		}
		free(path);
		if ((find_shortest_path(table, rooms, &path)) == 2)
			return (free_solution(&table, &begin, rooms, ret));
	}
	if (ants == 0)
		ft_printf("\x1b[33mF for ants\n\x1b[0m");
	if (!path)
		ft_printf("\x1b[33mF for paths\n\x1b[0m");
	restruct_table(table, begin, rooms);
	create_solution(graph, begin, rooms, &flows);
	print_solution(*graph, flows);
	free_solution(&table, &begin, rooms, 0);
	free(flows);
	return (0);
}

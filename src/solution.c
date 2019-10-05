/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solution.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiyellow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 18:43:27 by tiyellow          #+#    #+#             */
/*   Updated: 2019/10/05 23:48:58 by gwyman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			*create_flows(int **paths, int n, int ants, int sum)
{
	int i;
	int *flows;
	int j;
	int len;
	int k;
	int len_next;

	i = -1;
	flows = (int*)malloc(sizeof(int) * (n + 1));
	while (++i < n)
		flows[i] = 0;
	flows[i] = -1;
	i = 0;
	while (paths[i][0] == paths[0][0])
		i++;
	k = i;
	i = 0;
	while (i < k)
	{
		flows[i]++;
		if (paths[i][0] / 2 - 2 + flows[i] < paths[k][0])
			i = 0;
		else
		{
			i = 0;
			while (paths[i][0] <= paths[k][0])
				i++;
			k = paths[i][0];
		}
	}
}

int			create_solution(t_graph **graph, int **table, int rooms)
{
	int	*path;
	int ants;
	int sum;
	int n;
	int i;

	find_shortest_path(table, rooms, &path);
	sum = 0;
	i = -1;
	n = 0;
	ants = (*graph)->ants;
	while (path)
	{
		n++;
		sum += path[0] / 2 - 1;
		table[path[2]][path[3]] = 0;
		add_path(&((*graph)->paths), rooms * 2, &path);
		if (sum >= ants)
			break ;
		find_shortest_path(table, rooms, &path);
	}
	print_paths((*graph)->paths);
	ft_printf("ants	%d vs sum %d\n", ants, sum);
	create_flows((*graph)->paths, n, ants, sum);
	return (0);
}

void		print_solution(void)
{
}

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
	if (!(table = double_table((*graph)->table))
			|| !(begin = tab_dup(table, rooms)))
		return (1);
	if ((ret = find_shortest_path(table, rooms, &path)) != 0)
	{
		if (ret == 2)
			return (1);
		else
		{
			ft_printf("no path gg wp\n");
			return (0);
		}
	}
	while (ants && path)
	{
		ants--;
		reweight(table, path);
		free(path);
		find_shortest_path(table, rooms, &path);
	}
	restruct_table(table, begin, rooms);
	if (path)
		free(path);
	if (create_solution(graph, begin, rooms))
		return (1);
	return (0);
}

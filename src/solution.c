/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solution.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiyellow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 18:43:27 by tiyellow          #+#    #+#             */
/*   Updated: 2019/10/06 23:11:34 by sts              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

char		*create_str(int n, char *room)
{
	char	*s;

	s = ft_strnew(1);
	s[0] = 'L';
	s = ft_strrejoin(s, ft_itoa(n));
	s = ft_strrejoin(s, "-");
	s = ft_strrejoin(s, room);
	s = ft_strrejoin(s, " ");
	return (s);
}

void		print_solution(t_graph *graph, int *flows)
{
	char **turns;
	int i;
	int j;
	int n;
	int start;
	int curr;
	char *str;
	int need;

	i = -1;
	need = (graph->paths)[0][0] / 2 - 1 + flows[0];
	turns = (char**)malloc(sizeof(char*) * (need + 1));
	while (++i < need)
		turns[i] = ft_strnew(0);
	turns[i] = NULL;
	i = -1;
	curr = 1;
	while (flows[++i] != -1)
	{
		start = -1;
		while (flows[i] > 0)
		{
			j = 4;
			start++;
			n = start;
			while (j <= (graph->paths)[i][0])
			{
				str = create_str(curr, (graph->list)[(graph->paths)[i][j] / 2 - 1]);
				turns[n] = ft_strrejoin(turns[n], str);
				n++;
				j += 2;
			}
			flows[i]--;
			curr++;
		}
	}
	i = -1;
	while (turns[++i])
		ft_printf("%s\n", turns[i]);
}

void		print_flows(int *flows)
{
	int i;

	i = -1;
	while (flows[++i] != -1)
		ft_printf("%d ", flows[i]);
	ft_printf("F\n");
}

int			*create_flows(int **paths, int n, int ants, int sum)
{
	int i;
	int *flows;
	int k;

	i = -1;
	k = sum;
	flows = (int*)malloc(sizeof(int) * (n + 1));
	while (++i < n)
		flows[i] = 0;
	flows[i] = -1;
	i = 0;
	while (paths[i] && paths[i][0] != 1 && paths[i][0] == paths[0][0])
		i++;
	k = i;
	i = 0;
	while (ants > 0 && i < k)
	{
		if (paths[k] && paths[k][0] != 1 && i + 1 != k
				&& (paths[i][0] / 2 - 2 + flows[i]) == (paths[k][0] / 2 - 2))
		{
			i++;
			continue ;
		}
		if (i + 1 == k)
		{
			if (paths[k] && paths[k][0] != 1
					&& (paths[i][0] / 2 - 2 + flows[i]) == (paths[k][0] / 2 - 2))
			{
				i = 0;
				while (paths[i] && paths[i][0] != 1 && paths[i][0] <= paths[k][0])
					i++;
				k = i;
				i = 0;
				continue ;
			}
			flows[i]++;
			ants--;
			i = 0;
			continue ;
		}
		flows[i]++;
		ants--;
		i++;
	}
	print_flows(flows);
	return (flows);
}

int			create_solution(t_graph **graph, int **table, int rooms)
{
	int	*path;
	int ants;
	int sum;
	int n;
	int *flows;

	find_shortest_path(table, rooms, &path);
	sum = 0;
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
	flows = create_flows((*graph)->paths, n, ants, sum);
	print_solution(*graph, flows);
	return (0);
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

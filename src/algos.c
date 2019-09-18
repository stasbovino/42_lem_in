/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algos.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiyellow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 18:43:27 by tiyellow          #+#    #+#             */
/*   Updated: 2019/09/18 23:05:47 by gwyman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
/*
void		realloc_paths(t_grath **grath, int plus, int flag)
{
	int		len;
	int		**newpath;
	int		i;
	int		j;

	j = -1;
	len = flag ? 0 : 1;
	while (!flag && ((*grath)->paths)[len][0] != 0)
		len++;
	len += plus;
	newpath = (int**)malloc(sizeof(int*) * (len + 1));
	while (++j < len + 1)
	{
		i = -1;
		newpath[j] = (int*)malloc(sizeof(int) * ((*grath)->rooms + 1));
		if (flag || j > len - plus)
			while (++i < (*grath)->rooms  1)
				newpath[j][i] = 0;
	}
	i = -1;
	while (!flag && ++i < len - plus + 1)
	{
		j = -1;
		while (++j < (*grath)->rooms + 1)
			newpath[i][j] = ((*grath)->paths)[i][j];
		free(((*grath)->paths)[i]);
	}
	if (!flag)
		free((*grath)->paths)
	(*grath)->paths = newpath;
}
*/
/*
void		dijkstra(t_graph **graph, int *path, int longer, int node)
{
	int		i;

	if (path[0] == (*graph)->rooms)
	{
//		if (path[path[0]] != (*graph)->rooms)
//			path[path[0]] = 0;
		return ;
	}
	if (path[0] > 0 && node)
	{
//		path[path[0]] = 0;
		return ;
	}
	if (node == (*graph)->rooms)
	{
		if (path[0] >= longer
			&& ((*graph)->path)[0] > path[0])
		{
			(*graph)->path = path;
			ft_printf("LEN %d\n", path[0]);
		}
		else
		{
//			path[node] = 0;
			return ;
		}
	}
	i = 0;
	while (++i <= (*graph)->rooms)
	{
		if ((*graph)->table[node][i])
		{
			path[0]++;
			path[path[0]] = i;
		   	ft_printf("node: %d | jump to: %d| len: %d\n", node, i, path[0]);
			dijkstra(graph, path, longer, i);
			path[0]--;
		}
		ft_printf("%d\n", i);
	}
	ft_printf("\n");
//	path[path[0]] = 0;
	return ;
}
*/

void		init_alg(t_graph **abs_graph)
{
	t_graph		*graph;
	int			*path;
	int			*shortest;

	shortest = NULL;
	graph = *abs_graph;
	init_path(&path, graph->rooms);
	path[0] = 1;
	path[1] = 1;
 /*
 *	моя дикстра
 *	еще я добавила функции
 *	print_path(int *path, int rooms)
 *	init_path(int **path, int rooms)
 *	юзай на здоровье как г-рится
 */
	find_shortest_path(tab_dup(graph->table, graph->rooms), graph->rooms, path, &shortest);
 /*
  *	решение в shortest лежит
  */
	ft_printf("SOLUTION:\n");
	if (shortest)
		print_path(shortest, graph->rooms);
	else
		ft_printf("\x1b[31mno path\n\x1b[0m");
//	dijkstra(&graph, path, 0, 1);
	free(path);
}

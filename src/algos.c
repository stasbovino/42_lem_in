/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algos.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiyellow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 18:43:27 by tiyellow          #+#    #+#             */
/*   Updated: 2019/09/17 22:42:11 by tiyellow         ###   ########.fr       */
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

void		init_alg(t_graph **abs_graph)
{
	int			i;
	int			*path;
	t_graph		*graph;

	graph = *abs_graph;
	path = (int*)malloc(sizeof(int) * graph->rooms + 1);
	i = -1;
	while (++i < graph->rooms + 1)
		path[i] = 0;
	i = -1;
	while (++i < graph->rooms + 1)
		ft_printf("%d ", path[i]);
	ft_printf("\n");
	dijkstra(&graph, path, 0, 1);
	i = -1;
	while (++i < graph->rooms + 1)
		ft_printf("%d ", path[i]);
	free(path);
}

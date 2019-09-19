/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algos.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiyellow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 18:43:27 by tiyellow          #+#    #+#             */
/*   Updated: 2019/09/19 01:23:19 by sts              ###   ########.fr       */
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
/*
void		add_path(t_graph **graph, int **path)
{
	int	**ret;
	int	i;
	int	j;

	i = 0;
//	if (!((*graph)->paths))
//		i++;
	while ((*graph)->paths && (*graph)->paths[i])
		i++;
	ret = (int **)malloc(sizeof(int*) * (i + 1));
	j = -1;
	while ((*graph)->paths[++j])
	{
		i = -1;
		ret[j] = (int*)malloc(sizeof(int) * ((*graph)->rooms + 2);
		while (++i < (*graph)->rooms + 1)
			ret[j][i] = (*graph)->table[j][i];
	}
	i = -1;
	while (++i < (*graph)->rooms + 1)
		ret[j][i] = 0;
}
*/
void		node_chomper(t_graph **graph, int **path)
{
	int	i;
	int	j;

	i = 1;
	while (*path && (*path)[++i] && (*path)[i] != (*graph)->rooms)
	{
		j = 0;
		while(++j <= (*graph)->rooms)
		{
			if ((*graph)->table[(*path)[i]][j])
			{
				(*graph)->table[(*path)[i]][j] = 0;
				(*graph)->table[j][(*path)[i]] = 0;
			}
		}
		(*path)[i] = 0;
	}
	if (*path)
		free((*path));
}

void		init_alg(t_graph **abs_graph)
{
	t_graph		*graph;
	int		*path;
	int		*shortest;



	graph = *abs_graph;
	shortest = NULL;
	init_path(&path, graph->rooms); 
	find_sp(tab_dup(graph->table, graph->rooms), graph->rooms, path, &shortest);
/*	ft_printf("SOLUTION:\n");
	if (shortest)
	{
		print_path(shortest);
	}
	else
		ft_printf("\x1b[31mno path\n\x1b[0m");*/
	while (shortest != NULL)
	{
		add_path(&graph, &shortest);
/*		if (!(graph->paths[1][0] == 1))
		{
			if () //тут костыль для того чтобы проверить, нужны нам вообще смежные пути или нет i.e. если смежный путь длинее самого короткого и у нас мало муравьев то проще их пустить по самому короткому
		}*/
		node_chomper(&graph, &shortest);
		print_tab(graph->table, graph->rooms);
//		print_path(shortest);
		shortest = NULL;
		init_path(&path, graph->rooms);
		find_sp(tab_dup(graph->table, graph->rooms), graph->rooms, path, &shortest);
	}
	ft_printf("SOLUTION:\n");
	print_paths(graph->paths);
/*
	if (shortest)
	{
		print_path(shortest);
		free(shortest);
	}
	else
		ft_printf("\x1b[31mno path\n\x1b[0m");*/
}

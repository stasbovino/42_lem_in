/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_shortest_path.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwyman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 22:39:10 by gwyman-m          #+#    #+#             */
/*   Updated: 2019/09/19 01:20:35 by sts              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			fill_queue(int **queue, int ***table, int *path, int rooms)
{
	int j;
	int	node;
	int	i;
	int	links;

	i = -1;
	j = 0;
	links = 0;
	node = path[path[0]];
	while (++j < (rooms + 2))
		if ((*table)[node][j] == 1)
		{
			links++;
			(*queue)[++i] = (*table)[0][j];
			(*table)[node][j] = 0;
			(*table)[j][node] = 0;
		}
	if (links == 0)
		return (1);
	return (0);
}

void		find_sp_free(int ***table, int rooms, int **path, int **queue)
{
	if (queue)
		free(*queue);
	free(*path);
	free_tables(table, NULL, rooms);
}

void		find_shortest_path(int **table, int rooms, int *path, int **shortest)
{
	int *queue;
	int	nodes;

	if (path[path[0]] == rooms)
	{
		if (!*shortest)
		{
			*shortest = dup_path(path, rooms);
//			ft_printf("\x1b[32mfirst shortest!\x1b[0m\n");
			find_sp_free(&table, rooms, &path, NULL);
			return ;
		}
		if (*shortest)
		{
			//free's
			if ((*shortest)[0] <= path[0])
			{
//				ft_printf("\x1b[31mpath is bigger that shortest\x1b[0m\n");
				find_sp_free(&table, rooms, &path, NULL);
				return ;
			}
			else
			{
//				ft_printf("\x1b[32mnew shortest!\x1b[0m\n");
				free(*shortest);
				*shortest = dup_path(path, rooms);
				find_sp_free(&table, rooms, &path, NULL);
				return ;
			}
		}
	}
/*	ft_printf("\nBEGIN %d\n", path[path[0]]);
	print_tab(table, rooms);
*/	init_path(&queue, rooms);
	if (fill_queue(&queue, &table, path, rooms))
	{
		find_sp_free(&table, rooms, &path, &queue);
//		ft_printf("no links\n");
		return ;
	}
/*	print_queue(queue);
	print_path(path, rooms);
	ft_printf("AFTER REPLACE:\n");
	print_tab(table, rooms);
*/	nodes = -1;
	path[0] += 1;
	while (queue[++nodes] != 0)
	{
		path[path[0]] = queue[nodes];
/*		ft_printf("new path: go for %d\n", queue[nodes]);
		print_path(path, rooms);
*/		find_shortest_path(tab_dup(table, rooms), rooms, dup_path(path, rooms), shortest);
	}
	find_sp_free(&table, rooms, &path, &queue);
}

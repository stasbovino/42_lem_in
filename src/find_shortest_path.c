/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_shortest_path.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwyman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 22:39:10 by gwyman-m          #+#    #+#             */
/*   Updated: 2019/09/19 17:07:13 by gwyman-m         ###   ########.fr       */
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
	(*queue)[0] = 0;
	(*queue)[1] = 0;
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

static int	find_sp_free(int ***table, int rooms, int **path, int **queue)
{
	if (queue)
		free(*queue);
	free(*path);
	free_tables(table, NULL, rooms);
	return (1);
}

static void	free_and_dup(int **shortest, int *path, int rooms)
{
	free(*shortest);
	*shortest = dup_path(path, rooms);
}

int			find_sp(int **table, int rooms, int *path, int **shortest)
{
	int *queue;
	int	nodes;

	if (path[path[0]] == rooms)
	{
		if (!*shortest)
			*shortest = dup_path(path, rooms);
		else if (path[0] < (*shortest)[0])
			free_and_dup(shortest, path, rooms);
		return (find_sp_free(&table, rooms, &path, NULL));
	}
	if (*shortest)
		if (path[0] >= (*shortest)[0])
			return (find_sp_free(&table, rooms, &path, NULL));
	init_path(&queue, rooms);
	if (fill_queue(&queue, &table, path, rooms))
		return (find_sp_free(&table, rooms, &path, NULL));
	nodes = -1;
	path[0] += 1;
	while (queue[++nodes] != 0)
	{
		path[path[0]] = queue[nodes];
		find_sp(tab_dup(table, rooms), rooms, dup_path(path, rooms), shortest);
	}
	return (find_sp_free(&table, rooms, &path, NULL));
}

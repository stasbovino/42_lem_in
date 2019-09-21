/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_shortest_paths.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwyman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 16:22:11 by gwyman-m          #+#    #+#             */
/*   Updated: 2019/09/21 21:05:07 by gwyman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	fill_queue(int **queue, int ***table, int *path, int rooms)
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

static int find_sh_paths_free(int ***table, int rooms,
		int **path, int **queue)
{
	if (queue)
		free(*queue);
	free(*path);
	free_tables(table, NULL, rooms);
	return (1);
}

static int			init_len(int **table, int rooms, int i, int len)
{
	static int *path_len = NULL;
	int			j;

	if (!path_len || !lasts)
	{
		path_len = (int*)malloc(sizeof(int) * (rooms + 2));
		j = -1;
		while (++j < (rooms + 2))
			path_len[j] = 0;
	}
	j = i;
	while (++j < (rooms + 2))
	{
		if (table[i][j] == 1)
		{
			if (path_len[j] > len || path_len[j] == 0)
			{
				ft_printf("new len for %d: %d\n", j, len);
				path_len[j] = len;
			}
		}
	}
	len++;
	j = i;
	while (++j < (rooms + 2))
	{
		if (table[i][j] == 1)
		{
			init_len(table, rooms, j, len);
		}
	}
	if (i == 1)
	{
		j = -1;
		while (++j < (rooms + 2))
		{
			ft_printf("%d.%d\n", j + 1, path_len[j]);
		}
	}
	return (path_len[rooms] + 1);
}

int			find_sh_paths(int **table, int rooms, int *path, int ***shortests)
{
	int			*queue;
	int			nodes;
	static int	last = 0;

	if (last == 0)
	{
		last = init_len(table, rooms, 1, 1);
		ft_printf("LEN IS %d\n", last);
	}
	if (path[path[0]] == rooms)
	{
//		ft_printf("%d vs %d\n", path[0], last);
//		if (!(last == 0 || (last != 0 && path[0] > last)))
		if (path[0] < last)
			return (find_sh_paths_free(&table, rooms, &path, NULL));
		add_path(shortests, rooms, &path);
/*		if (!*shortests)
			add_path(shortests, rooms, &path);
		else if (path[0] <= (*shortests)[0][0])
		{
			if (path[0] < (*shortests)[0][0])
			{
				free_paths(shortests);
				*shortests = NULL;
			}
			add_path(shortests, rooms, &path);
 		}
*/		return (find_sh_paths_free(&table, rooms, &path, NULL));
	}
//	if (*shortests && path[0] >= (*shortests)[0][0])
	if (path[0] >= last)
		return (find_sh_paths_free(&table, rooms, &path, NULL));
	init_path(&queue, rooms);
	if (fill_queue(&queue, &table, path, rooms))
		return (find_sh_paths_free(&table, rooms, &path, &queue));
	nodes = -1;
	path[0] += 1;
	while (queue[++nodes] != 0)
	{
		path[path[0]] = queue[nodes];
		find_sh_paths(tab_dup(table, rooms), rooms, dup_path(path, rooms), shortests);
	}
	if (*shortests && path[0] <= 2)
	{
		last = (*shortests)[0][0];
		ft_printf("new last %d\n", last);
	}
	return (find_sh_paths_free(&table, rooms, &path, &queue));
}

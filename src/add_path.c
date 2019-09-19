/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwyman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 17:58:54 by gwyman-m          #+#    #+#             */
/*   Updated: 2019/09/19 20:40:13 by gwyman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	cpy_path(int **dest, int *src)
{
	int		i;

	i = -1;
	while (src[++i] != 0)
		(*dest)[i] = src[i];
}

int		**re_init_table(int ***old, int rooms)
{
	int **new;
	int	i;
	int	len;

	len = rooms * 2;
	new = (int**)malloc(sizeof(int*) * (len + 1));
	i = -1;
	while (++i < len)
	{
		init_path(&(new[i]), rooms);
		if (i < rooms)
		{
			cpy_path(&(new[i]), (*old)[i]);
			free((*old)[i]);
		}
	}
	new[i] = NULL;
	free(*old);
	return (new);
}

void	add_path(t_graph **graph, int **path)
{
	t_graph *g;
	int		i;
	int		rooms;

	g = *graph;
	rooms = g->rooms;
	if (g->paths == NULL)
	{
		i = -1;
		g->paths = (int**)malloc(sizeof(int*) * (rooms + 1));
		while (++i < rooms)
			init_path(&((g->paths)[i]), rooms);
		(g->paths)[i] = NULL;
	}
	i = 0;
	while ((g->paths)[i] && (g->paths)[i][0] != 1)
		i++;
	if ((g->paths)[i])
	{
		cpy_path(&((g->paths)[i]), *path);
//		free(*path);
	}
	else
	{
		g->paths = re_init_table(&(g->paths), i);
		add_path(graph, path);
	}
}

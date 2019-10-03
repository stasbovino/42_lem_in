/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_shortest_path.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwyman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/02 17:48:36 by gwyman-m          #+#    #+#             */
/*   Updated: 2019/10/03 17:13:13 by gwyman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static	int	free_and_return(int **visited, int **queue, int ret)
{
	if (visited)
		free(*visited);
	if (queue)
		free(*queue);
	return (ret);
}

static int	create_path(int **s, int rooms, int *visited)
{
	int j;
	int	n;
	int	*path;
	int	len;

	if (init_path(&path, rooms))
		return (1);
	if (init_path(s, rooms))
		return (free_and_return(&path, NULL, 1));
	j = rooms - 1;
	path[0] = rooms;
	n = 1;
	while (j != 0)
	{
		path[n++] = visited[j];
		j = visited[j] - 1;
	}
	len = 0;
	while (path[len] != 0)
		len++;
	n = 0;
	(*s)[n] = len;
	while (len > 0)
		(*s)[++n] = path[--len];
	return (free_and_return(&path, NULL, 0));
}

static int	prepare_for_find(t_graph *graph, int **queue, int **visited)
{
	if (init_path(queue, graph->rooms - 1))
		return (2);
	(*queue)[1] = 0;
	if (init_path(visited, graph->rooms - 1))
		return (free_and_return(NULL, queue, 2));
	(*visited)[1] = 0;
	return (0);
}

int			find_shortest_path(t_graph *graph, int **s)
{
	int	*queue;
	int	*visited;
	int	j;
	int	i;

	if (prepare_for_find(graph, &queue, &visited) != 0)
		return (2);
	while (queue[0] != 0)
	{
		i = queue[0];
		j = 0;
		pop_from_queue(&queue);
		while (++j < (graph->rooms + 2))
			if ((graph->table)[i][j] == 1 && visited[j - 1] == 0)
			{
				visited[j - 1] = i;
				push_to_queue(&queue, j);
				if (j == graph->rooms && create_path(s, graph->rooms, visited))
					return (free_and_return(&visited, &queue, 2));
				else if (j == graph->rooms)
					return (free_and_return(&visited, &queue, 0));
			}
	}
	*s = NULL;
	return (free_and_return(&visited, &queue, 1));
}

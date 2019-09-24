/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solution.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiyellow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 18:43:27 by tiyellow          #+#    #+#             */
/*   Updated: 2019/09/24 03:09:53 by sts              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			find_shortest_path(t_graph *graph, int *path, int **s)
{
	int			i;
	int			j;
	int			n;
	static int	*queue = NULL;
	static int	*len_paths = NULL;
	int			*new_queue;

	if (queue == NULL)
	{
		i = 1;
		j = 1;
		n = 0;
		queue = (int*)malloc(sizeof(int) * (rooms + 1));
		while (++j < (rooms + 2))
			if ((graph->table)[i][j] == 1)
			{
				queue[n] = j;
				n++;
			}
		queue[n] = 0;
	}
	if (len_paths = NULL)
	{

	}
	i = 1;
	j = 1;
	while (++j < (rooms + 2))
	{
	}
}
/*
void		create_solution()
{
}

void		print_solution()
{
}
*/
void		find_solution(t_graph **abs_graph)
{
	t_graph *graph;
	int		*path;
	int		*shortest;

	graph = *abs_graph;
	shortest = NULL;
	init_path(&path, graph->rooms);
	find_shortest_path(graph->table, graph->rooms, &shortest);
	print_path(shortest);
//	print_solution();
}

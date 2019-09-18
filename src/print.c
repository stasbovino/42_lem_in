/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwyman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 19:52:18 by gwyman-m          #+#    #+#             */
/*   Updated: 2019/09/19 01:15:36 by sts              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	print_tab(int **int_table, int rooms)
{
	int i;
	int j;

	i = -1;
	ft_printf("TABLE:\n");
	while (++i < (rooms + 2))
	{
		j = -1;
		while (++j < (rooms + 2))
			ft_printf("%d ", int_table[i][j]);
		ft_printf("\n");
	}
}

void	print_graph(t_graph *graph)
{
	int i;

	i = -1;
	ft_printf("rooms are: %d\n", graph->rooms);
	ft_printf("ants are: %d\n", graph->ants);
	while ((graph->list)[++i])
		ft_printf("%d %s\n", i + 1, (graph->list)[i]);
	print_tab(graph->table, graph->rooms);
}

void		print_path(int *path, int rooms)
{
	int i;

	i = 0;
	ft_printf("len of path: %d\n", path[0]);
	while (++i < (rooms + 2))
		ft_printf("%d ", path[i]);
	ft_printf("\n");
}

void		print_queue(int *queue)
{
	int i;

	i = -1;
	ft_printf("queue:\n");
	while (queue[++i] != 0)
		ft_printf("%d ", queue[i]);
	ft_printf("\n");
}

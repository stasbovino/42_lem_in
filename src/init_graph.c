/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_graph.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwyman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 17:00:24 by gwyman-m          #+#    #+#             */
/*   Updated: 2019/10/03 17:02:27 by gwyman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_graph	*init_graph(char **table, int **int_table, int rooms, int ants)
{
	t_graph *graph;

	if (!(graph = (t_graph*)malloc(sizeof(t_graph))))
		return (free_all(&table, &int_table, rooms, rooms));
	graph->rooms = rooms;
	graph->ants = ants;
	graph->table = int_table;
	graph->list = table;
	graph->paths = NULL;
	graph->flows = NULL;
	return (graph);
}

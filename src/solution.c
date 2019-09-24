/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solution.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiyellow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 18:43:27 by tiyellow          #+#    #+#             */
/*   Updated: 2019/09/24 23:19:35 by sts              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
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
	int		*shortest;

	graph = *abs_graph;
	shortest = NULL;
	find_shortest_path(graph, &shortest);
	print_path(shortest);
	free(shortest);
//	print_solution();
}

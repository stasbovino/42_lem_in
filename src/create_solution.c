/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_solution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwyman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 15:46:48 by gwyman-m          #+#    #+#             */
/*   Updated: 2019/10/10 16:42:58 by sts              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	free_and_null(int **f)
{
	if (*f)
		free(*f);
	*f = NULL;
}

int			create_solution(t_graph **graph, int **table, int rooms, int **f)
{
	int	*path;
	int n;
	int *flows;
	int ret;

	if ((ret = find_shortest_path(table, rooms, &path)) == 1)
		return (-2);
	free_and_null(f);
	if (ret == 2)
		return (-1);
	n = 0;
	while (path)
	{
		n++;
		table[path[2]][path[3]] = 0;
		if (ret = add_path(&((*graph)->paths), rooms * 2, &path))
			return (-1);
		ret = find_shortest_path(table, rooms, &path);
		if (ret == 2)
			return (-1);
	}
	if (!(flows = create_flows((*graph)->paths, n, (*graph)->ants)))
		return (-1);
	*f = flows;
	return (flows[0] + (*graph)->paths[0][0] / 2 - 2);
}

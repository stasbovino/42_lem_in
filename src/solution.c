/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solution.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiyellow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 18:43:27 by tiyellow          #+#    #+#             */
/*   Updated: 2019/10/05 20:39:46 by tiyellow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
/*
int			create_solution(t_graph **graph, )
{
}


void		print_solution()
{
}
*/

void		reweight(t_graph **graph, int *path)
{
	int	end;
	int	i;

	i = 2;
	end = path[path[0]];
	while (path[i + 1] != end)
	{
		(*graph)->table[path[i]][path[i + 1]] -= 1;
		(*graph)->table[path[i + 1]][path[i + 1]] += 1;
		i++;
	}
}

void		find_solution(t_graph **graph)
{
	int ants;
	int	*path;

	ants = (*graph)->ants;
	find_shortest_path(*graph, &path);
	while (ants && path)
	{
		if (path)
		{
			ants--;
			reweight(graph, path);
			free(path);
		}
		find_shortest_path(*graph, &path);
	}
	if (path)
		free(path);
	find_shortest_path(*graph, &path);
	while (path)
	{
		if (path)
			add_path(&((*graph)->paths), rooms * 2, &path);
		find_shortest_path(*graph, &path);
	}

/*	int	ret;

	ret = create_solution();
	if (ret == 2)
	{
	}
	else if (ret == 1)
	{
	}
	*/
}

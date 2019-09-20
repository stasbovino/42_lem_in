/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algos.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiyellow <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 18:43:27 by tiyellow          #+#    #+#             */
/*   Updated: 2019/09/20 18:20:00 by gwyman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		node_chomper(t_graph **graph, int **path)
{
	int	i;
	int	j;

	i = 1;
	while (*path && (*path)[++i] && (*path)[i] != (*graph)->rooms)
	{
		j = 0;
		while(++j <= (*graph)->rooms)
		{
			if ((*graph)->table[(*path)[i]][j])
			{
				(*graph)->table[(*path)[i]][j] = 0;
				(*graph)->table[j][(*path)[i]] = 0;
			}
		}
		(*path)[i] = 0;
	}
	if (*path)
		free((*path));
}

void		init_alg(t_graph **abs_graph)
{
	t_graph		*graph;
	int		*path;
	int		*shortest;



	graph = *abs_graph;
	shortest = NULL;
	init_path(&path, graph->rooms); 
	find_sp(tab_dup(graph->table, graph->rooms), graph->rooms, path, &shortest);


//int				find_sh_paths(int **table, int rooms, int *path, int ***shortests);
//новая функция, записывает в shortests (указатель на int**) таблицу путей
//
//перед применением int **shortests = NULL, init_path(&path, rooms)
//проще функцию наверное отдельную сделать для всего этого ^^^^



/*	ft_printf("SOLUTION:\n");
	if (shortest)
	{
		print_path(shortest);
	}
	else
		ft_printf("\x1b[31mno path\n\x1b[0m");*/
	while (shortest != NULL)
	{
		add_path(&graph, &shortest);
/*		if (!(graph->paths[1][0] == 1))
		{
			if () //тут костыль для того чтобы проверить, нужны нам вообще смежные пути или нет i.e. если смежный путь длинее самого короткого и у нас мало муравьев то проще их пустить по самому короткому
		}*/
		node_chomper(&graph, &shortest);
		print_tab(graph->table, graph->rooms);
//		print_path(shortest);
		shortest = NULL;
		init_path(&path, graph->rooms);
		find_sp(tab_dup(graph->table, graph->rooms), graph->rooms, path, &shortest);
	}
	ft_printf("SOLUTION:\n");
	print_paths(graph->paths);
/*
	if (shortest)
	{
		print_path(shortest);
		free(shortest);
	}
	else
		ft_printf("\x1b[31mno path\n\x1b[0m");*/
}

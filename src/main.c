/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwyman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 18:45:13 by gwyman-m          #+#    #+#             */
/*   Updated: 2019/09/18 14:43:08 by gwyman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int	main(void)
{
	char	**input;
	int		size;
	int		i;
	t_graph *graph;

	i = -1;
	size = 0;
	input = read_input(&size);
	ft_printf("size: %d\n", size);
	if (input == NULL)
	{
		ft_printf("error\n");
		get_next_line(0, NULL, 1);
		return (1);
	}
	else
	{
		while (++i < size)
		{
			ft_printf("%s\n", input[i]);
		}
		i = -1;
		if (!(graph = create_table(input, size)))
		{
			ft_printf("ERROR: invalid graph\n");
		}
		print_graph(graph);
//		init_alg(&graph);
		get_next_line(0, NULL, 1);
		free_input(&input, size);
		free_graph(&graph);
	}
	return (0);
}

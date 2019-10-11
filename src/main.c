/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwyman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 18:45:13 by gwyman-m          #+#    #+#             */
/*   Updated: 2019/10/11 19:03:25 by gwyman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	print_input(char **input, int size)
{
	int i;

	i = -1;
	while (++i < size)
	{
		ft_putstr(input[i]);
		ft_putchar('\n');
	}
	ft_putchar('\n');
}

static void	print_sol_err(int ret)
{
	if (ret == -1)
		return ;
	if (ret == 1)
		ft_putstr("ERROR: Not a single path from start to end\n");
	else
		ft_putstr("ERROR: malloc returned NULL\n");
}

static int	print_and_return(char *s)
{
	ft_putstr(s);
	return (1);
}

int			main(void)
{
	char	**input;
	int		size;
	int		ret;
	t_graph *graph;

	ret = 1;
	input = read_input(&size, -1, 0);
	if (input == NULL)
		return (print_and_return("ERROR: invalid reading\n"));
	print_input(input, size);
	if (!(graph = create_table(input, size)))
		ft_putstr("ERROR: invalid graph\n");
	else
	{
		if ((ret = find_solution(&graph, graph->rooms * 2, NULL, INT_MAX)))
			print_sol_err(ret);
		free_graph(&graph);
	}
	if (ret != 0 && ret != -1)
		ret = 1;
	free_input(&input, size);
	get_next_line(0, NULL, 1);
	return (ret);
}

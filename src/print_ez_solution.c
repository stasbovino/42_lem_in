/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ez_solution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwyman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 18:43:22 by gwyman-m          #+#    #+#             */
/*   Updated: 2019/10/11 18:51:03 by gwyman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		print_ez_solution(t_graph *graph)
{
	int		ants;
	char	*end;
	int		n;

	ants = graph->ants;
	end = graph->list[graph->rooms - 1];
	n = 1;
	while (ants != 0)
	{
		write(1, "L", 1);
		ft_putnbr(n);
		write(1, "-", 1);
		ft_putstr(end);
		write(1, " ", 1);
		ants--;
		n++;
	}
	write(1, "\n", 1);
	return (-1);
}

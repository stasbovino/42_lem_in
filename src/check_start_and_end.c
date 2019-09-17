/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_start_and_end.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwyman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 20:14:14 by gwyman-m          #+#    #+#             */
/*   Updated: 2019/09/17 20:31:08 by gwyman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	if_command(char **input, int count, int *var, int i)
{
	if (*var == 1)
		return (1);
	if (((i + 1) == count || input[i + 1][0] == '#'
				|| ft_countwords(input[i + 1]) != 3))
		return (1);
	(*var)++;
	return (0);
}

int			check_start_and_end(char **input, int count)
{
	int i;
	int	start;
	int	end;

	i = -1;
	start = 0;
	end = 0;
	while (++i < count)
		if (input[i][0] == '#' && input[i][1] == '#')
		{
			if (ft_strcmp(input[i], "##start") == 0)
			{
				if (if_command(input, count, &start, i))
					return (1);
			}
			else if (ft_strcmp(input[i], "##end") == 0)
			{
				if (if_command(input, count, &end, i))
					return (1);
			}
		}
	if (start == 0 || end == 0)
		return (1);
	return (0);
}

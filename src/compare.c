/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwyman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 19:32:21 by gwyman-m          #+#    #+#             */
/*   Updated: 2019/09/17 19:33:01 by gwyman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		compare_coords(char *input, char **split)
{
	int x1;
	int	x2;
	int	y1;
	int y2;
	int	i;

	i = 0;
	x1 = ft_atoi(split[1]);
	y1 = ft_atoi(split[2]);
	while (input[i] != ' ')
		i++;
	while (input[i] == ' ')
		i++;
	x2 = ft_atoi(input + i);
	while (input[i] != ' ')
		i++;
	while (input[i] == ' ')
		i++;
	y2 = ft_atoi(input + i);
	if (x1 == x2 && y1 == y2)
		return (1);
	return (0);
}

int		compare_names(char *input, char *name)
{
	int	i;

	i = 0;
	while (name[i] && input[i] && input[i] == name[i])
	{
		i++;
		if (input[i] == ' ' && name[i] == '\0')
			return (1);
	}
	return (0);
}

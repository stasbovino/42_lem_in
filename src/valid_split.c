/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwyman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 18:46:32 by gwyman-m          #+#    #+#             */
/*   Updated: 2019/09/09 19:12:11 by gwyman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		free_split(char ***split, int words, int ret)
{
	int i;

	i = -1;
	while (++i < words)
		free((*split)[i]);
	free(*split);
	return (ret);
}

int		check_split(char ***split, int words)
{
	int i;

	if (words == 3)
	{
		i = 0;
		if ((*split)[0][0] == 'L')
		{
			ft_printf("L at room name\n");
			return (free_split(split, words, 1));
		}
		while (++i < 3)
			if (check_isnum((*split)[i]) || check_overflow((*split)[i]))
			{
				ft_printf("nonu/overflow at room's coords\n");
				return (free_split(split, words, 1));
			}
	}
	else if (words == 2)
	{
		i = -1;
		while (++i < 2)
			if ((*split)[i][0] == 'L')
			{
				ft_printf("L at room name at links\n");
				return (free_split(split, words, 1));
			}
	}
	if (words == 3)
		ft_printf("room is ok\n");
	else
		ft_printf("link is ok\n");
	return (free_split(split, words, 0));
}

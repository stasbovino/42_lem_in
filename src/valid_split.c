/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwyman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 18:46:32 by gwyman-m          #+#    #+#             */
/*   Updated: 2019/09/17 19:39:26 by gwyman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		check_dup_room(char **input, int count, char **split)
{
	int		i;
	int		ret;

	i = 0;
	while (i < count && find_no_room(input[i]))
		i++;
	i--;
	while (++i < count && ((ret = find_no_room(input[i])) != 1))
	{
		if (ret == 2)
			continue ;
		if (compare_names(input[i], split[0]))
			return (1);
		if (compare_coords(input[i], split))
			return (1);
	}
	return (0);
}

int		check_exist_room(char **input, int count, char **split)
{
	int		i;
	int		first;
	int		second;
	int		ret;

	first = 0;
	second = 0;
	i = 0;
	if (ft_strcmp(split[0], split[1]) == 0)
		return (1);
	while (i < count && find_no_room(input[i]))
		i++;
	i--;
	while (++i < count && ((ret = find_no_room(input[i])) != 1))
	{
		if (ret == 2)
			continue ;
		if (first == 0 && compare_names(input[i], split[0]))
			first++;
		else if (second == 0 && compare_names(input[i], split[1]))
			second++;
		if (first && second)
			return (0);
	}
	return (1);
}

int		check_split(char **input, int count, char ***split, int words)
{
	int i;

	if (words == 3)
	{
		i = 0;
		if ((*split)[0][0] == 'L')
			return (free_split(split, words, 1));
		while (++i < 3)
			if (check_isnum((*split)[i]) || check_overflow((*split)[i]))
				return (free_split(split, words, 1));
		if (check_dup_room(input, count, *split))
			return (free_split(split, words, 1));
	}
	else if (words == 2)
	{
		i = -1;
		while (++i < 2)
			if ((*split)[i][0] == 'L')
				return (free_split(split, words, 1));
		if (check_exist_room(input, count, *split))
			return (free_split(split, words, 1));
	}
	return (free_split(split, words, 0));
}

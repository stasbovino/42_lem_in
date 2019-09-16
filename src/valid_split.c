/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwyman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 18:46:32 by gwyman-m          #+#    #+#             */
/*   Updated: 2019/09/16 20:52:58 by gwyman-m         ###   ########.fr       */
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

int		check_dup_room(char **input, int count, char **split)
{
	int		i;
	int		ret;

	i = 0;
	while (i < count && find_no_room(input[i]))
		i++;
	while (i < count && ((ret = find_no_room(input[i])) != 1))
	{
		if (ret == 2)
		{
			i++;
			continue ;
		}
		if (compare_names(input[i], split[0]))
		{
			ft_printf("room with that name is already exist\n");
			return (1);
		}
		if (compare_coords(input[i], split))
		{
			ft_printf("duple coords\n");
			return (1);
		}
		i++;
	}
	return (0);
}

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
	{
		ft_printf("loop at link\n");
		return (1);
	}
	while (i < count && find_no_room(input[i]))
		i++;
	while (i < count && ((ret = find_no_room(input[i])) != 1))
	{
		if (ret == 2)
		{
			i++;
			continue ;
		}
		if (first == 0 && compare_names(input[i], split[0]))
			first++;
		else if (second == 0 && compare_names(input[i], split[1]))
			second++;
		if (first && second)
			return (0);
		i++;
	}
	ft_printf("not existing/duple room at link!\n");
	return (1);
}

int		check_split(char **input, int count, char ***split, int words)
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
				return (free_split(split, words, 1));
			}
		if (check_dup_room(input, count, *split))
		{
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
		if (check_exist_room(input, count, *split))
		{
			return (free_split(split, words, 1));
		}
	}
	if (words == 3)
		ft_printf("room is ok\n");
	else
		ft_printf("link is ok\n");
	return (free_split(split, words, 0));
}

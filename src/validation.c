/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwyman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 18:45:10 by gwyman-m          #+#    #+#             */
/*   Updated: 2019/09/12 13:26:41 by gwyman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		check_link(char *buf)
{
	int	pos;
	int count;

	pos = ft_strchrpos(buf, '-');
	count = ft_countchars(buf, '-');
	if (count != 1)
		return (1);
	if (pos == 0 || (pos == (int)(ft_strlen(buf) - 1)))
		return (1);
	return (0);
}

int		check_valid(char *buf, int count)
{
	char	**split;
	int		words;

	if (!buf || !*buf)
		return (1);
	if (buf[0] == '#')
		return (0);
	if (count == 0)
	{
		if (buf[0] == '-' || check_isnum(buf) || check_overflow(buf) || ft_atoi(buf) == 0)
		{
			ft_printf("ants count is not ok\n");
			return (1);
		}
		ft_printf("ants count is ok\n");
		return (0);
	}
	words = count_words(buf);
	if (words != 3 && words != 1)
	{
		ft_printf("wrong words:%d\n", words);
		return (1);
	}
	if (words == 1 && check_link(buf))
	{
		ft_printf("one word is not link\n");
		return (1);
	}
	split = (words == 3) ? ft_strsplit(buf, ' ') : ft_strsplit(buf, '-');
	words = (words == 1) ? 2 : words;
	if (check_split(&split, words))
		return (1);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwyman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 18:45:10 by gwyman-m          #+#    #+#             */
/*   Updated: 2019/10/11 18:00:22 by gwyman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			count_chars(char *s)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (s[i] && s[i] != ' ')
	{
		if (s[i] == '-')
			count++;
		i++;
	}
	return (count);
}

static int	detect_bad_symbols(char *s)
{
	int	spaces;
	int	links;

	spaces = ft_countchars(s, ' ');
	links = count_chars(s);
	if (s[0] == 'L')
		return (1);
	if ((links != 0 && spaces != 0) || (links == 0 && spaces == 0))
		return (1);
	if (links != 0 && links != 1)
		return (1);
	if (spaces != 0 && spaces != 2)
		return (1);
	return (0);
}

int			check_ants(char *buf)
{
	if (buf[0] == '-' || check_isnum(buf)
			|| check_overflow(buf) || ft_atoi(buf) == 0)
	{
		ft_putstr("invalid ants\n");
		return (1);
	}
	return (0);
}

static int	check_words(char *buf, int words, int *prev)
{
	if (*prev == 0)
		*prev = words;
	if (words != 3 && words != 1)
		return (1);
	if (words > *prev)
		return (1);
	else
		*prev = words;
	if (words == 1 && check_link(buf))
		return (1);
	return (0);
}

int			check_valid(char **input, int count, char *buf, int useful)
{
	char		**split;
	int			words;
	static int	prev = 0;

	if (buf[0] == '#')
		return (0);
	if (useful == 0)
		return (check_ants(buf));
	if (detect_bad_symbols(buf))
	{
		ft_putstr("bad symb\n");
		return (1);
	}
	words = count_words(buf);
	if (check_words(buf, words, &prev))
		return (1);
	split = (words == 3) ? ft_strsplit(buf, ' ') : ft_strsplit(buf, '-');
	if (!split)
		return (1);
	words = (words == 1) ? 2 : words;
	if (check_split(input, count, &split, words))
		return (1);
	return (0);
}

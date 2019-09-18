/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_and_check_func.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwyman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 18:49:08 by gwyman-m          #+#    #+#             */
/*   Updated: 2019/09/18 02:59:07 by sts              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		check_link(char *buf)
{
	int	i;
	int	before;
	int	after;
	int	link;

	i = -1;
	before = 0;
	after = 0;
	link = 0;
	while (buf[++i])
	{
		if (buf[i] == '-' && link == 0)
			link++;
		else if (buf[i] == '-' && link != 0)
			return (1);
		else if (buf[i] != '-' && link == 0)
			before++;
		else if (buf[i] != '-' && link == 1)
			after++;
	}
	if (!after || !before)
		return (1);
	return (0);
}

int		check_isnum(char *num)
{
	int i;

	i = (num[0] == '-') ? 0 : -1;
	if (!num[i + 1])
		return (1);
	while (num[++i])
		if (!(num[i] >= '0' && num[i] <= '9'))
			return (1);
	return (0);
}

int		check_overflow(char *num)
{
	int		i;
	char	*overf;
	int		j;
	int		numlen;

	overf = (num[0] == '-') ? "-2147483648" : "2147483647";
	i = (num[0] == '-') ? 0 : -1;
	j = i + 1;
	while (num[++i])
		if (num[i] != '0')
			break ;
	numlen = ft_strlen(num) - i;
	if (numlen > 10)
		return (1);
	else if (numlen < 10)
		return (0);
	while (num[i])
	{
		if (num[i] > overf[j])
			return (1);
		i++;
		j++;
	}
	return (0);
}

int		count_words(char *buf)
{
	int		k;
	size_t	i;

	i = 0;
	k = 0;
	while (buf[i])
	{
		if (buf[i] && buf[i] != ' ')
		{
			while (buf[i] && buf[i] != ' ')
				i++;
			k++;
		}
		else if (buf[i] && buf[i] == ' ')
		{
			if (i == 0)
				return (-1);
			if (buf[i + 1] && buf[i + 1] == ' ')
				return (-1);
		}
		if (!buf[i])
			break ;
		i++;
	}
	return (k);
}

int		count_rooms(char **input, int size)
{
	int i;
	int	count;
	int	ret;

	count = 0;
	i = 0;
	while (++i < size)
	{
		ret = find_no_room(input[i]);
		if (ret == 1)
			break ;
		if (ret == 0)
			count++;
	}
	return (count);
}

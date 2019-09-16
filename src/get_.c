/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwyman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 17:42:06 by gwyman-m          #+#    #+#             */
/*   Updated: 2019/09/16 23:10:54 by gwyman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		find_no_room(char *s)
{
	int i;

	i = -1;
	if (s[0] == '#')
		return (2);
	if (count_words(s) != 3)
		return (1);
	while (s[++i])
	{
		if (s[i] == '-')
			return (1);
	}
	return (0);
}

char	*get_first_word(char *input)
{
	int		i;
	int		len;
	char	*word;

	len = 0;
	while (input[len] != ' ')
		len++;
	word = (char*)malloc(sizeof(char) * (len + 1));
	word[len] = '\0';
	i = -1;
	while (++i < len)
		word[i] = input[i];
	return (word);
}

char	*get_next_room_name(char **input, int size, int opt)
{
	static int	last = 0;
	int			ret;
	int			tmp;
	static int	start = 0;
	static int	end = 0;

	if (last == 0)
	{
		while (last < size && (input[last][0] == '#' || ft_countwords(input[last]) != 3))
			last++;
		last--;
	}
	if (opt == 0)
	{
		tmp = 0;
		while (tmp < size && ft_strcmp(input[tmp], "##start") != 0)
			tmp++;
		while (tmp < size && (input[tmp][0] == '#' || ft_countwords(input[tmp]) != 3))
			tmp++;
		start = tmp;
		return (get_first_word(input[tmp]));
	}
	else if (opt != -1)
	{
		tmp = 0;
		while (tmp < size && ft_strcmp(input[tmp], "##end") != 0)
			tmp++;
		while (tmp < size && (input[tmp][0] == '#' || ft_countwords(input[tmp]) != 3))
			tmp++;
		end = tmp;
		return (get_first_word(input[tmp]));
	}
	while (++last < size)
	{
		if (last == start || last == end)
			continue ;
		ret = find_no_room(input[last]);
		if (ret == 0)
			return (get_first_word(input[last]));
		if (ret == 1)
			return (NULL);
	}
	return (NULL);
}

int		find_no_link(char *s)
{
	int i;

	i = -1;
	if (s[0] == '#')
		return (1);
	while (s[++i])
		if (s[i] == '-')
			return (0);
	return (1);
}

char	*get_next_link(char **input, int size)
{
	static int	last = 0;
	int			ret;

	if (last == 0)
	{
		while (find_no_link(input[last]))
			last++;
		last--;
	}
	while (++last < size)
	{
		ret = find_no_link(input[last]);
		if (ret == 0)
			return (input[last]);
		if (ret == 1)
			return (NULL);
	}
	return (NULL);
}

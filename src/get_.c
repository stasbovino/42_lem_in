/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwyman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 17:42:06 by gwyman-m          #+#    #+#             */
/*   Updated: 2019/09/25 18:00:40 by sts              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

char		*get_first_word(char *input)
{
	int		i;
	int		len;
	char	*word;

	len = 0;
	while (input[len] != ' ')
		len++;
	if (!(word = (char*)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	word[len] = '\0';
	i = -1;
	while (++i < len)
		word[i] = input[i];
	return (word);
}

static char	*get_next_room_name_opt(char **input, int size, int opt, int *v)
{
	int		tmp;
	char	*compare;

	compare = (opt == 0) ? "##start" : "##end";
	tmp = 0;
	while (tmp < size && ft_strcmp(input[tmp], compare) != 0)
		tmp++;
	while (tmp < size &&
			(input[tmp][0] == '#' || ft_countwords(input[tmp]) != 3))
		tmp++;
	*v = tmp;
	return (get_first_word(input[tmp]));
}

char		*get_next_room_name(char **in, int n, int opt)
{
	static int	last = 0;
	int			ret;
	static int	start = 0;
	static int	end = 0;

	if (last == 0)
	{
		while (last < n &&
				(in[last][0] == '#' || ft_countwords(in[last]) != 3))
			last++;
		last--;
	}
	if (opt != -1)
		return (get_next_room_name_opt(in, n, opt, (opt == 0) ? &start : &end));
	while (++last < n)
	{
		if (last == start || last == end)
			continue ;
		ret = find_no_room(in[last]);
		if (ret == 0)
			return (get_first_word(in[last]));
		if (ret == 1)
			return (NULL);
	}
	return (NULL);
}

char		*get_next_link(char **input, int size)
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

int			get_ants_num(char **input, int size)
{
	int i;

	i = 0;
	while (i < size && input[i][0] == '#')
		i++;
	return (ft_atoi(input[i]));
}

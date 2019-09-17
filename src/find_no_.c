/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_no_.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwyman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 19:29:14 by gwyman-m          #+#    #+#             */
/*   Updated: 2019/09/17 19:30:22 by gwyman-m         ###   ########.fr       */
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

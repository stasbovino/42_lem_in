/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwyman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 20:15:30 by gwyman-m          #+#    #+#             */
/*   Updated: 2019/10/03 20:32:00 by gwyman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static char	**read_error(char ***input, int count, char **buf)
{
	int i;

	i = 0;
	if (buf)
		free(*buf);
	if (input)
	{
		while (i < count)
		{
			free((*input)[i]);
			i++;
		}
		free(*input);
	}
	return (NULL);
}

static char	**re_init(char ***input, int count)
{
	char	**tmp;
	int		i;
	int		j;

	i = 0;
	if (!(tmp = (char**)malloc(sizeof(char*) * (count + SIZE))))
		return (NULL);
	while (i < count)
	{
		if (!(tmp[i] = ft_strdup((*input)[i])))
		{
			j = -1;
			while (++j < i)
				free(tmp[j]);
			free(tmp);
			return (read_error(input, count, NULL));
		}
		i++;
	}
	i = -1;
	while (++i < count)
		free((*input)[i]);
	free((*input));
	return (tmp);
}

static int	write_to_arr(char ***input, int *count, char **buf)
{
	if (!((*input)[*count] = ft_strdup(*buf)))
		return (1);
	free(*buf);
	*buf = NULL;
	(*count)++;
	return (0);
}

char		**read_input(int *size, int useful, int count)
{
	char	**input;
	char	*buf;
	int		r;

	buf = NULL;
	if (!(input = (char**)malloc(sizeof(char*) * SIZE)))
		return (read_error(NULL, 0, NULL));
	while ((r = get_next_line(0, &buf, 0)))
	{
		if (r == -1 || !buf || !*buf)
			return (read_error(&input, count, &buf));
		useful += (buf[0] != '#') ? 1 : 0;
		if (check_valid(input, count, buf, useful))
			return (read_error(&input, count, &buf));
		if (write_to_arr(&input, &count, &buf))
			return (read_error(&input, count, &buf));
		if (count % SIZE == 0)
			if (!(input = re_init(&input, count)))
				return (NULL);
	}
	if (check_start_and_end(input, count))
		return (read_error(&input, count, NULL));
	*size = count;
	return (input);
}

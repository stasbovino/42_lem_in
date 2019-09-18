/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwyman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 20:15:30 by gwyman-m          #+#    #+#             */
/*   Updated: 2019/09/18 03:05:59 by sts              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static char	**re_init(char ***input, int count)
{
	char	**tmp;
	int		i;

	i = 0;
	tmp = (char**)malloc(sizeof(char*) * (count + SIZE));
	while (i < count)
	{
		tmp[i] = ft_strdup((*input)[i]);
		free((*input)[i]);
		i++;
	}
	free(*input);
	return (tmp);
}

static char	**read_error(char ***input, int count, char **buf)
{
	int i;

	i = 0;
	if (buf)
		free(*buf);
	while (i < count)
	{
		free((*input)[i]);
		i++;
	}
	free(*input);
	return (NULL);
}

static void	write_to_arr(char ***input, int *count, char **buf)
{
	(*input)[*count] = ft_strdup(*buf);
	free(*buf);
	*buf = NULL;
	(*count)++;
}

char		**read_input(int *size)
{
	char	**input;
	char	*buf;
	int		r;
	int		count;
	int		useful;

	useful = -1;
	count = 0;
	buf = NULL;
	input = (char**)malloc(sizeof(char*) * SIZE);
	while ((r = get_next_line(0, &buf, 0)))
	{
		if (r == -1 || !buf || !*buf)
			return (read_error(&input, count, &buf));
		if (buf[0] != '#')
			useful++;
		if (check_valid(input, count, buf, useful))
			return (read_error(&input, count, &buf));
		write_to_arr(&input, &count, &buf);
		if (count % SIZE == 0)
			input = re_init(&input, count);
	}
	if (check_start_and_end(input, count))
		return (read_error(&input, count, NULL));
	*size = count;
	return (input);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwyman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 18:45:13 by gwyman-m          #+#    #+#             */
/*   Updated: 2019/09/17 17:44:32 by gwyman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

char	**re_init(char ***input, int count)
{
	char	**tmp;
	int		i;

	i = 0;
	tmp = (char**)malloc(sizeof(char*) * (count + 2));
	while (i < count)
	{
		tmp[i] = ft_strdup((*input)[i]);
		free((*input)[i]);
		i++;
	}
	free(*input);
	return (tmp);
}

char	**read_error(char ***input, int count, char **buf)
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

int		check_start_and_end(char **input, int count)
{
	int i;
	int	start;
	int	end;

	i = -1;
	start = 0;
	end = 0;
	while (++i < count)
	{
		if (input[i][0] == '#' && input[i][1] == '#')
		{
			if (ft_strcmp(input[i], "##start") == 0)
			{
				if (start == 1)
				{
					ft_printf("two starts\n");
					return (1);
				}
				if (((i + 1) == count || input[i + 1][0] == '#' || ft_countwords(input[i + 1]) != 3))
					return (1);
				start++;
			}
			else if (ft_strcmp(input[i], "##end") == 0)
			{
				if (end == 1)
				{
					ft_printf("two ends\n");
					return (1);
				}
				if (((i + 1) == count || input[i + 1][0] == '#' || ft_countwords(input[i + 1]) != 3))
					return (1);
				end++;
			}
		}
	}
	if (start == 0 || end == 0)
	{
		ft_printf("no start or no end\n");
		return (1);
	}
	return (0);
}

char	**read_input(int *size)
{
	char	**input;
	char	*buf;
	int		r;
	int		count;
	int		useful;

	useful = -1;
	count = 0;
	r = 0;
	buf = NULL;
	input = (char**)malloc(sizeof(char*) * 2);
	while ((r = get_next_line(0, &buf, 0)))
	{
		if (r == -1 || !buf || !*buf)
		{
			ft_printf("invalid read\n");
			return (read_error(&input, count, &buf));
		}
		if (buf[0] != '#')
			useful++;
		if (check_valid(input, count, buf, useful))
			return (read_error(&input, count, &buf));
		input[count] = ft_strdup(buf);
		free(buf);
		buf = NULL;
		count++;
		if (count % 2 == 0)
			input = re_init(&input, count);
	}
	if (check_start_and_end(input, count))
	{
		ft_printf("bad commands\n");
		return (read_error(&input, count, NULL));
	}
	*size = count;
	return (input);
}

int	main(void)
{
	char	**input;
	int		size;
	int		i;

	i = -1;
	size = 0;
	input = read_input(&size);
	ft_printf("size: %d\n", size);
	if (input == NULL)
	{
		ft_printf("error\n");
		get_next_line(0, NULL, 1);
		return (1);
	}
	else
	{
		while (++i < size)
		{
			ft_printf("%s\n", input[i]);
		}
		i = -1;
		if (create_table(input, size))
		{
			ft_printf("ERROR: invalid graph\n");
		}
		while (++i < size)
		{
			free(input[i]);
		}
		free(input);
		get_next_line(0, NULL, 1);
	}
	return (0);
}

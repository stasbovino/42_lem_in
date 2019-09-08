#include "lem_in.h"

static int	check_isnum(char *num)
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

static int	check_overflow(char *num)
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
			break;
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
		if (buf[i] != ' ')
		{
			while (buf[i] != ' ' && buf[i])
				i++;
			k++;
		}
		else if (buf[i] == ' ')
		{
			if (i == 0)
				return (-1);
			if (buf[i + 1] == ' ')
				return (-1);
		}
		i++;
	}
	return (k);
}

int		free_split(char ***split, int words, int ret)
{
	int i;

	i = -1;
	while (++i < words)
		free((*split)[i]);
	free(*split);
	return (ret);
}

int		check_split(char ***split, int words)
{
	int i;

	if (words == 3)
	{
		i = 0;
		if ((*split)[0][0] == 'L')
			return (free_split(split, words, 1));
		while (++i < 3)
			if (check_isnum((*split)[i]) || check_overflow((*split)[i]))
				return (free_split(split, words, 1));
	}
	else if (words == 2)
	{
		i = -1;
		while (++i < 2)
			if ((*split)[i][0] == 'L')
				return (free_split(split, words, 1));
	}
	return (free_split(split, words, 0));
}

int		check_valid(char *buf, int count)
{
	char	**split;
	int		words;

	if (!buf || !*buf)
		return (1);
	if (count == 0)
	{
		if (buf[0] == '-' || check_isnum(buf) || check_overflow(buf))
			return (1);
		return (0);
	}
	if (buf[0] == '#')
		return (0);
	words = count_words(buf);
	if (words != 3 && words != 1)
		return (1);
	split = (words == 3) ? ft_strsplit(buf, ' ') : ft_strsplit(buf, '-');
	words = (words == 1) ? 2 : words;
	if (check_split(&split, words))
		return (1);
	return (0);
}

char	**re_init(char ***input, int count)
{
	char	**new;
	int		i;

	i = 0;
	new = (char**)malloc(sizeof(char*) * (count + 10));
	while (i < count)
	{
		new[i] = ft_strdup((*input)[i]);
		free((*input)[i]);
	}
	free(*input);
	return (new);
}

char	**read_input(int *size)
{
	char	**input;
	char	*buf;
	int		r;
	int		count;

	count = 0;
	r = 0;
	buf = NULL;
	input = (char**)malloc(sizeof(char*) * 10);
	while ((r = get_next_line(0, &buf, 0)))
	{
		if (r == -1)
			return (NULL);
		input[count] = buf;
		if (check_valid(buf, count))
			return (NULL);
		count++;
		if (count % 10 == 0)
			input = re_init(&input, count);
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
	input = read_input(&size);
	if (input == NULL)
	{
		ft_printf("error\n");
		return (1);
	}
	else
	{
		while (++i < size)
		{
			ft_printf("%s\n", input[i]);
		}
	}
	return (0);
}

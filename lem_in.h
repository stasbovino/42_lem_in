/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwyman-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 19:07:36 by gwyman-m          #+#    #+#             */
/*   Updated: 2019/09/16 17:44:54 by gwyman-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"

char		**read_input(int *size);
char		**re_init(char ***input, int count);

int			create_table(char **input, int size);

int			check_link(char *buf);
int			check_valid(char *buf, int count);
int			check_isnum(char *num);
int			check_overflow(char *num);
int			count_words(char *buf);
int			count_rooms(char **input, int size);
int			check_split(char ***split, int words);
int			free_split(char ***split, int words, int ret);

int			find_no_room(char *s);
int			find_no_link(char *s);
char		*get_first_word(char *input);
char		*get_next_room_name(char **input, int size);
char		*get_next_link(char **input, int size);

#endif

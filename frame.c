/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbuy <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 18:55:35 by dbuy              #+#    #+#             */
/*   Updated: 2017/11/10 18:55:36 by dbuy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

t_tetrimin	*ft_mklst(t_tetrimin *t, char **sp, char c)
{
	int x;
	int y;
	int i;

	x = -1;
	y = -1;
	i = 0;
	if (!*sp || !(t->next = (t_tetrimin*)malloc(sizeof(t_tetrimin))))
		return (NULL);
	while (++x < 4)
	{
		while (++y < 4)
		{
			if (sp[x][y] == '#')
			{
				t->x[i] = x;
				t->y[i] = y;
				i++;
			}
		}
		y = -1;
	}
	t->c = c++;
	t->next = ft_mklst(t->next, sp + 4, c);
	return (t);
}

t_tetrimin	*convert_tetrs(char *buff)
{
	char		**sp;
	t_tetrimin	*t;

	sp = ft_strsplit(buff, '\n');
	if (sp_test(sp) > 0)
		return (NULL);
	ft_strdel(&buff);
	if (!(t = (t_tetrimin*)malloc(sizeof(t_tetrimin))))
		return (NULL);
	t = ft_mklst(t, sp, 'A');
	while (*sp)
		ft_strdel(sp++);
	sp = NULL;
	return (t);
}

char		**mkframe(int min)
{
	char	**frame;
	int		i;
	int		x;
	int		y;

	x = 0;
	y = 0;
	i = -1;
	if (!(frame = (char**)malloc(sizeof(char*) * (min + 1))))
		return (NULL);
	frame[min] = NULL;
	while (++i < min)
	{
		if (!(frame[i] = (char*)malloc(min + 1)))
			return (NULL);
		ft_memset(frame[i], '.', (size_t)min);
		frame[i][min] = '\0';
	}
	return (frame);
}

char		**ft_frame_back(int side, char **src, char c)
{
	int	x;
	int	y;

	x = -1;
	while (++x < side)
	{
		y = -1;
		while (++y < side)
			if (src[x][y] == c)
				src[x][y] = '.';
	}
	return (src);
}

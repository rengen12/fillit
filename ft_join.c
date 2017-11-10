/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_join.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbuy <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 14:09:13 by dbuy              #+#    #+#             */
/*   Updated: 2017/11/07 14:09:21 by dbuy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include "fillit.h"

char	**mkframe(int min)
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

char	**ft_frame_back(int side, char **src, char c)
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
	return(src);
}

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
	char **sp;
	t_tetrimin *t;

	sp = ft_strsplit(buff, '\n');
	if (sp_test(sp) > 0)
		return (NULL);
	ft_strdel(&buff);
	if (!(t = (t_tetrimin*)malloc(sizeof(t_tetrimin))))
		return (NULL);
	t = ft_mklst(t, sp, 'A');
	if (t == NULL)
		puts("TT = NULL>>>");
	while (*sp)
		ft_strdel(sp++);
	sp = NULL;
	return (t);

}

t_tetrimin 	*ft_new_xy(t_tetrimin *t, int x, int y)
{
	int xmin;
	int ymin;
	int i;

	ymin = 1000;
	xmin = 1000;
	i = -1;
	while (++i < 4)
	{
		if (t->x[i] < xmin)
			xmin = t->x[i];
		if (t->y[i] < ymin)
			ymin = t->y[i];
	}
	i = -1;
	while (++i < 4)
	{
		t->x[i] = t->x[i] - xmin + x;
		t->y[i] = t->y[i] - ymin + y;
	}
	return (t);
}

int		ft_find_place(int side, char **frame, t_tetrimin *t)
{
	int x;
	int y;
	int i;

	x = -1;
	y = -1;
	i = 0;
	while(++x < side)
	{
		y = -1;
		while (++y < side)
		{
			if (t->x[i] == x && t->y[i] == y && frame[x][y] != '.')
				return (0);
			if (t->x[i] == x && t->y[i] == y && frame[x][y] == '.')
				i++;
		}
	}
	if (i == 4)
		return (1);
	return (0);
}

char	**ft_add(int side, char **frame, t_tetrimin *t)
{
	int		x;
	int		y;
	int		i;

	x = -1;
	i = 0;
	while (++x < side)
	{
		y = -1;
		while (++y < side)
			if (t->x[i] == x && t->y[i] == y)
				if (i++ > -1)
					frame[x][y] = t->c;
		frame[x][y] = '\0';
	}
	frame[x] = NULL;
	return (frame);
}

char 	**ft_fill(int side, char **frame, t_tetrimin *t)
{
	char	**tmp;	
	int		x;
	int		y;

	tmp = NULL;
	if (t == NULL)
		return (frame);
	x = -1;
	while (++x < side)
	{
		y = -1;
		while (++y < side)
		{
			t = ft_new_xy(t, x, y);
			if (ft_find_place(side, frame, t) != 0)
				tmp = ft_fill(side, ft_add(side, frame, t), t->next);
			if (tmp != NULL)
				return (tmp);
			frame = ft_frame_back(side, frame, t->c);
		}
	}
	return (NULL);
}

void	ft_join(int side, t_tetrimin *t)
{
	char 	**frame;

	frame = mkframe(side);
	frame = ft_fill(side, frame, t);
	if (frame == NULL)
		ft_join(++side, t);
	ft_print_strtab(frame);
}
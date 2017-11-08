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

char	**mkframe(int min, char	**src, int xx, int yy)
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
	if (src != NULL)
	{
		while (x < min - xx)
		{
			while (y < min - yy)
			{
				frame[x][y] = src[x + xx][y + yy];
				y++;
			}
			y = 0;
			x++;
		}
	}
	return (frame);

}
int		find_min(int n)
{
	int sqr;
	int out;

	out = 0;
	sqr = n * 4;
	while (out <= sqr)
	{
		if (out * out >= sqr)
			return (out);
		out++;
	}
	return (0);
}

int        ft_evaluate(int n, char **frame)
{
    int x;
    int y;
    int count;

    x = -1;
    y = -1;
    count = 0;
//	ft_putstr("EVALUATE>>>\n");
//	ft_print_strtab(frame);
    while(++x < n)
    {
        while (++y < n)
            if (frame[x][y] != '.')
            {
                 // if (x < n - 1)
                 //     if (frame[x + 1][y] == '.')
                 //         count++;
                if (x > 0)
                    if (frame[x - 1][y] == '.')
                        count++;
                // if (y < n - 1)
                //     if (frame[x][y + 1] == '.')
                //         count++;
                if (y > 0)
                    if (frame[x][y - 1] == '.')
                        count++;                
            }
        y = -1;
    }
    //printf("EVALUATE = %d\n", count);
    return (count);
}

char	**ft_copy(int n, char **src)
{
	int		i;
	char	**frame;

	i = -1;
	if (!(frame = (char**)malloc(sizeof(char*) * (n + 1))))
		return (NULL);
	frame[n] = NULL;
	while (++i < n)
		frame[i] = ft_strdup(src[i]);
	return (frame);
}

char	**ft_find_place(int n, char **frame, t_tetrimin tetr_conv)
{
	int		x;
	int		y;
	int		i;
	int		best;
	int		eval;
	char	**optimal;

	x = 0;
	y = 0;
	i = 1;
	best = 9999;
	optimal = NULL;
	//printf("FIND PLACE... tetr number = %d\n", index);
	//printf("n = %d\n", n);
	while(x < n)
	{
		while (y < n)
		{
			if (frame[x + tetr_conv.x[0]][y + tetr_conv.y[0]] == '.')
			{
				//printf("x in struct = %d, y in strc %d\n", tetr_conv.x[0], tetr_conv.y[0]);
				if (x + tetr_conv.x[1] < n  && y + tetr_conv.y[1] < n  && \
					x + tetr_conv.x[2] < n  && y + tetr_conv.y[2] < n  && \
					x + tetr_conv.x[3] < n  && y + tetr_conv.y[3] < n )
				{
					if (frame[x + tetr_conv.x[0]][y + tetr_conv.y[0]] == '.' && \
						frame[x + tetr_conv.x[1]][y + tetr_conv.y[1]] == '.' && \
						frame[x + tetr_conv.x[2]][y + tetr_conv.y[2]] == '.' && \
						frame[x + tetr_conv.x[3]][y + tetr_conv.y[3]] == '.')
					{
						/*printf("0x frame = %d, y frame %d\n", x + tetr_conv.x[0], y + tetr_conv.y[0]);
						printf("1x frame = %d, y frame %d\n", x + tetr_conv.x[1], y + tetr_conv.y[1]);
						printf("2x frame = %d, y frame %d\n", x + tetr_conv.x[2], y + tetr_conv.y[2]);
						printf("3x frame = %d, y frame %d\n", x + tetr_conv.x[3], y + tetr_conv.y[3]);
						printf("char %c\n", frame[x + tetr_conv.x[0]][y + tetr_conv.y[0]]);*/
						frame[x + tetr_conv.x[0]][y + tetr_conv.y[0]] = tetr_conv.c;
						frame[x + tetr_conv.x[1]][y + tetr_conv.y[1]] = tetr_conv.c;
						frame[x + tetr_conv.x[2]][y + tetr_conv.y[2]] = tetr_conv.c;
						frame[x + tetr_conv.x[3]][y + tetr_conv.y[3]] = tetr_conv.c;
						//printf("char after %c\n", frame[x + tetr_conv.x[0]][y + tetr_conv.y[0]]);
						eval = ft_evaluate(n, frame);
						if (eval < best)
						{
							best = eval;
							optimal = ft_copy(n, frame);
//							printf("OPTIMAL:\n");
//							ft_print_strtab(optimal);
						}
						frame[x + tetr_conv.x[0]][y + tetr_conv.y[0]] = '.';
						frame[x + tetr_conv.x[1]][y + tetr_conv.y[1]] = '.';
						frame[x + tetr_conv.x[2]][y + tetr_conv.y[2]] = '.';
						frame[x + tetr_conv.x[3]][y + tetr_conv.y[3]] = '.';				
					}
				}
			}
			y++;
		}
		y = 0;
		x++;
	}
	//ft_putstr("RETURNING OPTIMAL>>>>>>>\n");
	//ft_print_strtab(optimal);
	//ft_putstr("FIND PLACE EXIT\n");
	return (optimal);
}

char	**ft_frame_back(int n, char **src, char c)
{
	//puts("FRAME_BACK>>>");
	//printf("Char = %c\n", c);
	//ft_print_strtab(src);
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (x < n)
	{
		while (y < n)
		{
			if (src[x][y] == c)
				src[x][y] = '.';
			y++;
		}
		y = 0;
		x++;
	}
	return(src);
}

void	ft_purify_pl(t_tetrimin *tetr_conv, int numbfig)
{
	int i;

	i = 0;
	while (i < numbfig)
		tetr_conv[i++].placed = 0;
}

char	**ft_fillframe(int n, char **frame, t_tetrimin *tetr_conv, int numbfig)
{
	int		i;
	int		j;
	int		opt;
	int		opt_index;
	int		current;
//	char 	**best;

	i = 0;
	j = 0;
	opt = -1;
	while (j < numbfig)
	{
		while (i < numbfig)
		{
			if (tetr_conv[i].placed == 0)
			{
				frame = ft_find_place(n, frame, tetr_conv[i]);
				if (!frame)
				{
					ft_purify_pl(tetr_conv, numbfig);
					return (NULL);
				}
				current = ft_evaluate(n, frame);
				if (opt == -1)
				{
					opt_index = i;
					opt = current;
				}
				if (current < opt)
				{
					opt_index = i;
					opt = current;
				}
//				printf("opt = %d, current = %d\n", opt, current);
				frame = ft_frame_back(n, frame, tetr_conv[i].c);
			}
				if (i == numbfig - 1)
				{
					puts("PLACING OPTIMAL ELEMENT>>>>>>>>>>>>>>>>");
					//printf("Optimal index = %d\n", opt_index);

					frame = ft_find_place(n, frame, tetr_conv[opt_index]);					
					tetr_conv[opt_index].placed = 1;
					ft_print_strtab(frame);					
				}
			
			i++;
		}
		opt = -1;
		i = 0;
		j++;
	}
	return (frame);
}

t_tetrimin *ft_norm_str(t_tetrimin *t)
{
	int i;
	int min_x;
	int min_y;

	i = -1;
	min_x = 4;
	min_y = 4;
	while (++i < 4)
	{
		if (t->x[i] < min_x)
			min_x = t->x[i];
		if (t->y[i] < min_y)
			min_y = t->y[i];		
	}
	i = -1;
	while (++i < 4)
	{
		t->x[i] -= min_x;
		t->y[i] -= min_y;		
	}
	// if (t->y[0] > 0)
	// 	min_y = t->y[0];
	// i = -1;
	// while (++i < 4)
	// 	t->y[i] -= min_y;		
	return (t);
}

void	ft_convert(t_tetrimin *t, char **m)
{
	int x;
	int y;
	int i;

	x = -1;
	y = -1;
	i = 0;
	while (++x < 4)
	{
		while (++y < 4)
		{
			if (m[x][y] == '#')
			{
				t->x[i] = x;
				t->y[i] = y;
				i++;
			}
		}
		y = -1;
	}
	t = ft_norm_str(t);
}

t_tetrimin	*convert_tetrs(int qfig, char ***tetr)
{
	t_tetrimin	*r;
	int			i;
	char		c;

	c = 'A';
	i = 0;
	if (!(r = (t_tetrimin *)malloc(sizeof(*r) * (qfig + 1))))
		return (NULL);
	while (*tetr)
	{
		ft_convert(&r[i], *tetr);
		r[i].c = c++;
		r[i].placed = 0;
		tetr++;
		i++;
	}
	return (r);
}

char **ft_norm_frame(int side, char **src)
{
	int x;
	int y;
	int count;
	int count2;

	x = 0;
	y = 0;
	count = 0;
	count2 = 0;
	//puts("NORM_FRAME!>>>>>>");
	while (x < side)
	{
		if (src[x][0] == '.')
			count++;
		if (src[0][x] == '.')
			count2++;
		x++;
	}
	if (count == side)
		y = 1;
	if (count2 == side)
		x = 1;
	else
		x = 0;
	//printf("x = %d; y = %d\n", x, y);
	src = mkframe(side, src, x, y);
	return (src);
}

void	ft_join(int j, int n, t_tetrimin *tetr_conv)
{
	int			i;
	char		**frame;
	int			side;

	i = -1;
	side = j + find_min(n);
	//ft_putstr("FT_JOIN....\n");
	if (!(frame = mkframe(side, NULL, 0, 0)))
		return ;
	if (!(frame = ft_fillframe(side, frame, tetr_conv, n)))
	{
		ft_strdel(frame);
		ft_putstr("EXPANDING SQUARE>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
		ft_join(j + 1, n, tetr_conv);
	}

	else
	{
		//frame = ft_norm_frame(side, frame);
		//frame = ft_norm_frame(side, frame);	
		//ft_putstr("\nFINAL PRINT>>>>>>>>>>>>>>>>>\n\n");
		//printf("%p\n", frame);
		ft_print_strtab(frame);
	}
}



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

#ifndef S_TETRIMIN
# define S_TETRIMIN
typedef struct	s_tetrimin
{
	int	x[4];
	int	y[4];
	char c;
}				t_tetrimin;

#endif
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
    ft_putstr("EVALUATE>>>\n");
    ft_print_strtab(frame);
    while(++x < n)
    {
        while (++y < n)
            if (frame[x][y] != '.')
            {
                if (x < n - 1)
                    if (frame[x + 1][y] == '.')
                        count++;
                if (x > 0)
                    if (frame[x - 1][y] == '.')
                        count++;
                if (y < n - 1)
                    if (frame[x][y + 1] == '.')
                        count++;
                if (y > 0)
                    if (frame[x][y - 1] == '.')
                        count++;                
            }
        y = -1;
    }
    printf("EVALUATE = %d\n", count);
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
	int x;
	int y;
	int i;
	int mineff;
	char	**optimal;

	x = 0;
	y = 0;
	i = 1;
	mineff = 9999;
	optimal = NULL;
	ft_putstr("FIND PLACE... \n");
	printf("n = %d\n", n);
	while(x < n)
	{
//		ft_putstr("WHILE1!...\n");
		while (y < n)
		{
//			ft_putstr("WHILE2!...\n");
			if (frame[x][y] == '.')
			{
				//ft_putstr("2IF!...\n");
				//ft_putstr("int %d %d %d %d\n%d %d %d %d\n");
				if (x + tetr_conv.x[1] < n  && y + tetr_conv.y[1] < n  && \
					x + tetr_conv.x[2] < n  && y + tetr_conv.y[2] < n  && \
					x + tetr_conv.x[3] < n  && y + tetr_conv.y[3] < n )
				{
					ft_putstr("3IF!...\n");
					if (frame[x + tetr_conv.x[1]][y + tetr_conv.y[1]] == '.' && \
						frame[x + tetr_conv.x[2]][y + tetr_conv.y[2]] == '.' && \
						frame[x + tetr_conv.x[3]][y + tetr_conv.y[3]] == '.')
					{
						ft_putstr("4IF!...\n");
						frame[x + tetr_conv.x[0]][y + tetr_conv.y[0]] = tetr_conv.c;
						frame[x + tetr_conv.x[1]][y + tetr_conv.y[1]] = tetr_conv.c;
						frame[x + tetr_conv.x[2]][y + tetr_conv.y[2]] = tetr_conv.c;
						frame[x + tetr_conv.x[3]][y + tetr_conv.y[3]] = tetr_conv.c;
						if (mineff > ft_evaluate(n, frame))
						{
							ft_putstr("LASTIF!...\n");
							mineff = ft_evaluate(n, frame);
							write(1, " T ", 3);
							printf("%d\n\n", mineff);
							optimal = ft_copy(n, frame);// копия фрейма
							printf("OPTIMAL:\n");
							ft_print_strtab(optimal);
							frame[x + tetr_conv.x[0]][y + tetr_conv.y[0]] = '.';
							frame[x + tetr_conv.x[1]][y + tetr_conv.y[1]] = '.';
							frame[x + tetr_conv.x[2]][y + tetr_conv.y[2]] = '.';
							frame[x + tetr_conv.x[3]][y + tetr_conv.y[3]] = '.';					
						}
					}
				}
			}
			y++;
		}
		y = 0;
		x++;
	}
	ft_putstr("RETURNING OPTIMAL>>>\n");
	printf("%p\n", frame);
	ft_print_strtab(optimal);
	return (optimal);
}


char	**ft_fillframe(int n, char **frame, t_tetrimin *tetr_conv, int numbfig) //полностью заполянет матрицу
{
	int		i;
	char 	**framebuff;

	framebuff = NULL;
	i = 0;
	while (i < numbfig)
	{
		printf("I = %d GGGGGGGGGGGG\n", i);		
		printf("ADRESS = %p\n", &tetr_conv[i]);
		if (!(frame = ft_find_place(n, frame, tetr_conv[i])))
		{
			printf("ADRESS IN FILL = %p\n", frame);
			ft_print_strtab(frame);
			//frame = framebuff;
			return (NULL);
		}
		i++;
		printf("ADRESS IN FILL BEFORE RETURN = %p\n", frame);
		ft_print_strtab(frame);
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
	//r[qfig] = NULL;
	while (*tetr)
	{
		ft_convert(&r[i], *tetr);
		r[i].c = c++;
		tetr++;
		i++;
	}
	return (r);
}

void	ft_join(int j, int n, t_tetrimin *tetr_conv)
{
	int			i;
	char		**frame;
	int			min;

	i = -1;
	min = j + find_min(n);
	ft_putstr("FT_JOIN....\n");
	if (!(frame = (char**)malloc(sizeof(char*) * (min + 1))))
		return ;
	frame[min] = NULL;
	while (++i < n)
	{
		if (!(frame[i] = (char*)malloc(min + 1)))
			return ;
		ft_memset(frame[i], '.', (size_t)min);
		frame[i][min] = '\0';
	}
	if (!(frame = ft_fillframe(min, frame, tetr_conv, n)))
	{
		//ft_delmem(frame);
		ft_putstr("FT_JOIN2....\n");
		ft_putstr("FRAME IN JOIN:\n");
		ft_print_strtab(frame);
		ft_join(j + 1, n, tetr_conv);
	}
	ft_putstr("FINAL PRINT\n");
	printf("%p\n", frame);
	ft_print_strtab(frame);
}



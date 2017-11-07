/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbuy <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 13:01:22 by dbuy              #+#    #+#             */
/*   Updated: 2017/11/04 13:01:23 by dbuy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

#ifndef S_TETRIMIN
# define S_TETRIMIN
typedef struct	s_tetrimin
{
	int	x[4];
	int	y[4];
	char c;
}				t_tetrimin;

#endif

int		ft_evaluate(int n, char **frame);
void	ft_join(int j, int n, t_tetrimin *tetr_conv);
t_tetrimin	*convert_tetrs(int qfig, char ***tetr);

int		ft_valid(char *buff)
{
	int i;
	int count;

	i = -1;
	count = 0;
	while (buff[++i] != '\0')
	{
		if (buff[i] != '.' && buff[i] != '#' && buff[i] != '\n')
			return (8);
		if (buff[i] == '.' || buff[i] == '#')
			count++;
		if (count > 4)
			return (4);
		if (i == 0 && buff[i] == '\n' && count != 4)
			return (1);
		if (buff[i] == '\n' && count == 4)
			count = 0;
		if (i > 1)
			if (buff[i] == '\n' && buff[i - 1] == '\n' && buff[i - 2] == '\n')
				return (2);
	}
	if (i != 19 && i % 20 != 1 && i % 20 != 0 && (i + 1) % 21 != 0)
	{
//		printf("i = %d\n", i);
		return (7);
	}
	return (0);
}

int		ft_tetr_num(char *buff)
{
	int i;
	int count;

	count = 0;
	i = -1;
	while (buff[++i] != '\0')
		if (buff[i] == '\n')
			count++;
	return (count == 3 ? 1 : (count / 5) + 1);
}

char	*ft_read(char *file)
{
	int		fd;
	char	*buff;

	if ((fd = open(file, O_RDONLY)) < 0)
		return (NULL);
	if (!(buff = (char*)malloc(10000)))
		return (NULL);
	read(fd, buff, 10000);
	return (buff);
}

char	***ft_fulltetr(char ***out, int n, int nn, char **split)
{
	int sp;

	sp = 0;
	while (split[sp])
	{
		while (nn < 4)
			out[n][nn++] = split[sp++];
		out[n++][nn] = NULL;
		nn = 0;
	}
	return (out);
}

char	***ft_gettetr(int i, char *buff, int n, int nn)
{
	char	***out;

	if (!(out = (char***)malloc(sizeof(char**) * (i + 1))))
		return (NULL);
	while (n++ < i)
	{
		if (!(out[n - 1] = (char**)malloc(sizeof(char*) * 5)))
			return (NULL);
		while (nn < 4)
			if (!(out[n - 1][nn++] = (char*)malloc(9)))
				return (NULL);
	}
	out[n - 1] = NULL;
	out = ft_fulltetr(out, 0, 0, ft_strsplit(buff, '\n'));
	return (out);
}

int		ft_test_tab(int **tab, int x, int y)
{
	int i;

	i = 0;
	while (i < 10)
	{
		if (tab[0][i] == x && tab[1][i] == y)
			return (1);
		i++;
	}
	return (0);
}

int		ft_rec(char **m, int x, int y, int **tab)
{
	int out;

	out = 0;
	if (x > 3 || y > 3 || y < 0)
		return (0);
	if (ft_test_tab(tab, x, y) == 1)
		return (0);
	if (m[x][y] != '#')
		return (0);
	else
	{
		tab[0][tab[2][0]] = x;
		tab[1][tab[2][0]] = y;
		tab[2][0]++;
		out++;
		out = out + ft_rec(m, x + 1, y, tab);
		out = out + ft_rec(m, x, y + 1, tab);
		out = out + ft_rec(m, x, y - 1, tab);
		return (out);
	}
}

int		ft_test_matrix(char **m, int x, int y, int **tab)
{
	if (x > 3 || y > 3 || y < 0)
		return (0);
	if (ft_test_tab(tab, x, y) == 1)
		return (0);
	while (x < 4)
	{
		while (y < 4)
		{
			if (m[x][y] == '#')
				return (ft_rec(m, x, y, tab));
			y++;
		}
		y = 0;
		x++;
	}
	return (0);
}

void	ft_settab(int **tab)
{
	int i;

	i = 0;
	while (i < 10)
	{
		tab[0][i] = -1;
		tab[1][i] = -1;
		i++;
	}
	tab[2][0] = 0;
}

int		ft_test_figchars(char **m)
{
	int i;
	int j;
	int count;

	i = 0;
	j = 0;
	count = 0;
	while (i < 4)
	{
		while (j < 4)
		{
			if (m[i][j] == '#')
				count++;
			j++;
		}
		j = 0;
		i++;
	}
	if (count != 4)
		return (1);
	return (0);
}

int		ft_valid_fig(char ***t)
{
	int **tab;
	int i;

	i = -1;
	tab = (int**)malloc(sizeof(int*) * 3);
	tab[0] = (int*)malloc(sizeof(int) * 17);
	tab[1] = (int*)malloc(sizeof(int) * 17);
	tab[2] = (int*)malloc(sizeof(int) * 1);
	tab[2][0] = 0;
	while (++i < 10)
	{
		tab[0][i] = -1;
		tab[1][i] = -1;
	}
	i = 0;
	while (*t)
	{
		i++;
		if (ft_test_figchars(*t) > 0)
			return (i);
		if (ft_test_matrix(*t++, 0, 0, tab) != 4)
			return (i);
		ft_settab(tab);
	}
	return (0);
}

void	print_tetriminos(char ***tetriminos)
{
	while (*tetriminos)
	{
		puts("NEXT");
		ft_print_strtab(*tetriminos);
//		printf("Eval = %d\n", ft_evaluate(4, *tetriminos));
		tetriminos++;
	}
}

int		print_errors(int i)
{
	if (i == 101)
		ft_putendl("Invalid argc");
	if (i == 102)
		ft_putendl("Invalid file");
	if (i == 103)
		ft_putendl("Invalid map");
	if (i == 104)
		ft_putendl("Cant make tetriminos matrix");
	if (i < 100)
	{
		ft_putstr("Invalid Fig ");
		ft_putendl(ft_itoa(i));
	}
	return (0);
}

int		main(int ac, char **av)
{
	char		***tetriminos;
	char		*buff;
	int			err;
	int			count;
	t_tetrimin	*tetr_converted;

	if (ac != 2)
		return (print_errors(101));
	if (!(buff = ft_read(av[1])))
		return (print_errors(102));
	if (ft_valid(buff) > 0)
	{
		printf("%d\n", ft_valid(buff));
		return (print_errors(103));
	}
	count = ft_tetr_num(buff);
	if (!(tetriminos = ft_gettetr(count, buff, 0, 0)))
		return (print_errors(104));
	err = ft_valid_fig(tetriminos);
	if (err > 0)
		return (print_errors(err));
	print_tetriminos(tetriminos);
	tetr_converted = convert_tetrs(count, tetriminos);
	ft_join(0, count, tetr_converted);
}

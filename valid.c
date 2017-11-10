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
#include <stdio.h>
#include "libft.h"
#include "fillit.h"

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
		if (((i + 1) % 21) == 0 && buff[i] != '\n')
			return (1);
	}
	if ((i + 1) % 21 != 0 || (i + 1) > 546)
		return (7);
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
	return ((count + 1) / 5);
}

char	*ft_read(char *file)
{
	int		fd;
	char	*buff;
    int     ret;

	if ((fd = open(file, O_RDONLY)) < 0)
		return (NULL);
	if (!(buff = (char*)malloc(1000)))
		return (NULL);
	ret = read(fd, buff, 1000);
    buff[ret] = '\0';
	if (close(fd) == -1)
		return (NULL);
	return (buff);
}

char	***ft_fulltetr(char ***out, int x, int y, char **split)
{
	int sp;

	sp = 0;
	while (split[sp])
	{
		while (y < 4)
			out[x][y++] = split[sp++];
		out[x++][y] = NULL;
		y = 0;
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

	i = -1;
	count = 0;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
			if (m[i][j] == '#')
				count++;
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

// void	print_tetriminos(char ***tetriminos)
// {
// 	while (*tetriminos)
// 	{
// 		//puts("NEXT");
// 		//ft_print_strtab(*tetriminos);
// 		tetriminos++;
// 	}
// }

int		print_errors(int i)
{
	if (i == 100)
		ft_putendl("usage: fillit target_file");
	if (i == 101)
		ft_putendl("error");
	return (0);
}

// void	print_t(t_tetrimin *t)
// {
// 	t_tetrimin *temp;
// 	int i;
// 	int j;

// 	i = -1;
// 	j = 0;
// 	temp = t;
// 	puts("PRINT_T");
// 	while (temp)
// 	{
// 		puts("While");
// 		while (++i < 4)
// 		{
// 			printf("j = %d; t.x[i] = %d; t.y[i] = %d; Char = %c\n", j, temp->x[i], temp->y[i], temp->c);
// 		}
// 		i = -1;
// 		j++;
// 		temp = temp->next;
// 	}
// }

int		main(int ac, char **av)
{
	char		***tetriminos;
	char		*buff;
	int			count;
	t_tetrimin	*t;

	if (ac == 1)
		return (print_errors(100));
	if (ac != 2)
		return (print_errors(101));
	if (!(buff = ft_read(av[1])))
		return (print_errors(101));
	if (ft_valid(buff) > 0)
		return (print_errors(101));
	count = ft_tetr_num(buff);
	if (!(tetriminos = ft_gettetr(count, buff, 0, 0)))
		return (print_errors(101));
	if (ft_valid_fig(tetriminos) > 0)
		return (print_errors(101));
//	print_tetriminos(tetriminos);
	t = convert_tetrs(tetriminos);
//	print_t(t);
	ft_join(find_min(count), t);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amichak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 13:00:18 by amichak           #+#    #+#             */
/*   Updated: 2017/11/11 13:00:20 by amichak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static char	*ft_read(char *file)
{
	int		fd;
	char	*buff;
	int		ret;

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

static int	find_min(char *buff)
{
	int i;
	int count;
	int sqr;
	int out;

	count = 0;
	i = -1;
	out = 2;
	while (buff[++i] != '\0')
		if (buff[i] == '\n')
			count++;
	sqr = 4 * ((count + 1) / 5);
	while (out <= sqr)
	{
		if (out * out >= sqr)
			return (out);
		out++;
	}
	return (0);
}

static int	print_errors(int i)
{
	if (i == 100)
		ft_putendl("usage: fillit target_file");
	if (i == 101)
		ft_putendl("error");
	return (0);
}

void		ft_tabdel(char **tab)
{
	if (!tab)
		return ;
	while (*tab)
		ft_strdel(tab++);
	tab = NULL;
}

int			main(int ac, char **av)
{
	char		*buff;
	t_tetrimin	*t;

	if (ac == 1)
		return (print_errors(100));
	if (ac != 2)
		return (print_errors(101));
	if (!(buff = ft_read(av[1])))
		return (print_errors(101));
	if (ft_valid(buff) > 0)
	{
		ft_strdel(&buff);
		return (print_errors(101));
	}
	if (!(t = convert_tetrs(buff)))
	{
		ft_strdel(&buff);
		return (print_errors(101));
	}
	ft_join(find_min(buff), t);
	ft_strdel(&buff);
	ft_tetrdel(&t);
	return (0);
}

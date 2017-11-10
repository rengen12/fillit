/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbuy <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 18:45:36 by dbuy              #+#    #+#             */
/*   Updated: 2017/11/10 18:45:39 by dbuy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int			sp_test(char **sp)
{
	if (!*sp)
		return (0);
	if (ft_test_figchars(sp) > 0)
		return (1);
	return (sp_test(sp + 4));
}

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

static int	print_errors(int i)
{
	if (i == 100)
		ft_putendl("usage: fillit target_file");
	if (i == 101)
		ft_putendl("error");
	return (0);
}

int			main(int ac, char **av)
{
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
	if (!(t = convert_tetrs(buff)))
		return (print_errors(101));
	ft_join(find_min(count), t);
	return (0);
}
